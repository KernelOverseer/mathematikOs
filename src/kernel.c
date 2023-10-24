#include "kernel.h"
#include "terminal/terminal.h"
#include "idt/idt.h"
#include "graphics/graphics.h"
#include "keyboard/keyboard.h"
#include "math/math.h"

#define DAMPING 0.8
#define CAMERA_PLANE_DIST 20
#define CAMERA_PLANE_WIDTH 30

#define MAP_W 10
#define MAP_H 10
#define MAP_SIZE 20

void draw_loop(void);

void kernel_main()
{
	idt_init();

	// int iter = 0;
	// int ipf = 1;
	while (1)
	{
		draw_loop();
		// if (iter % ipf == 0)
		// iter++;
	}
}

struct ray
{
	vector origin;
	vector direction;
};

struct camera
{
	float x;
	float y;
	float angle;
	vector direction;
	vector start;
	vector iteration;
	struct ray ray;
};

struct object
{
	float x;
	float y;
	float speed_x;
	float speed_y;
	float acc_x;
	float acc_y;
	struct camera camera;
};

uint8_t map[MAP_H][MAP_W] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

float get_map_intersection(struct ray ray, int *final_status)
{
	float distance = 100000;
	float temp_distance;
	int status;
	*final_status = 0;
	for (int i = 0; i < MAP_H; i++)
	{
		for (int j = 0; j < MAP_W; j++)
		{
			if (map[i][j])
			{
				vector p1 = vector_create(j * MAP_SIZE, i * MAP_SIZE);
				vector p2 = vector_create(j * MAP_SIZE + MAP_SIZE, i * MAP_SIZE);
				vector p3 = vector_create(j * MAP_SIZE + MAP_SIZE, i * MAP_SIZE + MAP_SIZE);
				vector p4 = vector_create(j * MAP_SIZE, i * MAP_SIZE + MAP_SIZE);
				status = 0;
				vector intersection = ft_intersect(ray.origin, ray.direction, p1, p2, &status);
				if (status)
				{
					temp_distance = vector_distance(ray.origin, intersection);
					if (temp_distance < distance)
					{
						distance = temp_distance;
						*final_status = 1;
					}
				}
				status = 0;
				intersection = ft_intersect(ray.origin, ray.direction, p2, p3, &status);
				if (status)
				{
					temp_distance = vector_distance(ray.origin, intersection);
					if (temp_distance < distance)
					{
						distance = temp_distance;
						*final_status = 1;
					}
				}
				status = 0;
				intersection = ft_intersect(ray.origin, ray.direction, p3, p4, &status);
				if (status)
				{
					temp_distance = vector_distance(ray.origin, intersection);
					if (temp_distance < distance)
					{
						distance = temp_distance;
						*final_status = 1;
					}
				}
				status = 0;
				intersection = ft_intersect(ray.origin, ray.direction, p4, p1, &status);
				if (status)
				{
					temp_distance = vector_distance(ray.origin, intersection);
					if (temp_distance < distance)
					{
						distance = temp_distance;
						*final_status = 1;
					}
				}
			}
		}
	}
	return distance;
}

void debug_draw_map(void)
{
	for (int i = 0; i < MAP_H; i++)
	{
		for (int j = 0; j < MAP_W; j++)
		{
			if (map[i][j] == 1)
				fill_rect(j * MAP_SIZE, i * MAP_SIZE, MAP_SIZE, MAP_SIZE, 20);
		}
	}
}

void move_player(struct object *player)
{
	if (is_key_pressed(KEY_A))
		player->camera.angle -= 0.1;
	if (is_key_pressed(KEY_D))
		player->camera.angle += 0.1;

	vector direction = vector_normalize(get_vector_from_angle(player->camera.angle));

	if (is_key_pressed(KEY_W))
	{
		player->acc_x += direction.x * 0.2;
		player->acc_y += direction.y * 0.2;
	}
	if (is_key_pressed(KEY_S))
	{
		player->acc_x -= direction.x * 0.2;
		player->acc_y -= direction.y * 0.2;
	}

	player->speed_x += player->acc_x;
	player->speed_y += player->acc_y;

	player->x += player->speed_x;
	player->y += player->speed_y;

	player->speed_x *= DAMPING;
	player->speed_y *= DAMPING;

	player->acc_x *= DAMPING;
	player->acc_y *= DAMPING;
}

void update_camera(struct object *player)
{
	player->camera.x = player->x;
	player->camera.y = player->y;

	player->camera.direction = vector_normalize(get_vector_from_angle(player->camera.angle));
	vector left = vector_mul(get_vector_from_angle(player->camera.angle - M_PI_2), CAMERA_PLANE_WIDTH/2);
	player->camera.start = vector_add(vector_mul(player->camera.direction, CAMERA_PLANE_DIST), left);
	player->camera.iteration = vector_mul(vector_normalize(left), -(float)CAMERA_PLANE_WIDTH / (float)VGA_WIDTH);
	player->camera.ray.origin = vector_create(player->camera.x, player->camera.y);
	player->camera.ray.direction = player->camera.start;
}

void debug_draw_player(struct object *player)
{
	vector direction_position;

	fill_rect(player->x - 2, player->y - 2, 5, 5, 10);
	direction_position = vector_add(vector_mul(player->camera.direction, 20), vector_create(player->x, player->y));
	draw_line(player->x, player->y, direction_position.x, direction_position.y, 20);
	
	draw_line(player->camera.x + player->camera.start.x,
	player->camera.y + player->camera.start.y,
	player->camera.x + player->camera.start.x + player->camera.iteration.x * VGA_WIDTH, player->camera.y + player->camera.start.y + player->camera.iteration.y * VGA_WIDTH, 21);
}

void raycast(struct object *player)
{
	for (int i = 0; i < VGA_WIDTH; i++)
	{
		int status;
		float distance = get_map_intersection(player->camera.ray, &status) / vector_size(player->camera.ray.direction);
		if (status)
		{
			float height = VGA_HEIGHT / distance;
			int top = (VGA_HEIGHT / 2.0) - (height / 2);
			int bottom = (VGA_HEIGHT / 2.0) + (height / 2);
			if (top < 0)
				top = 0;
			if (bottom > VGA_HEIGHT)
				bottom = VGA_HEIGHT;
			for (int j = top; j < bottom; j++)
			{
				int color = 0x10 + 15 / distance;
				if (color > 0x1F)
					color = 0x1F;
				set_pixel(i, j, color);
			}
		}
		player->camera.ray.direction = vector_add(player->camera.ray.direction, player->camera.iteration);
	}
}

void draw_loop(void)
{
	static struct object player = {50, 50, 0, 0, 0, 0};

	
	move_player(&player);
	update_camera(&player);

	clear_screen(0x0);
	// debug_draw_map();
	// debug_draw_player(&player);
	raycast(&player);
	blit_buffer();
}