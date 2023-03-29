#include "entity.h"

#include "sprite.h"

void initialise_entity(entity_t *entity, type_entity_enum type, int posX, int posY) {
	entity->type = type;
	entity->posX = posX;
	entity->posY = posY;
	entity->freeze = 0;
}

int posX_width_entity(entity_t entity) {
	int width = -1;

	if(entity.type == PLAYER) {
		width = entity.posX + width_sprite(SPRITE_PLAYER)-1;
	}
	else if(entity.type == ENEMY) {
		if(entity.enemy.type == PROBE) {
			width = entity.posX + width_sprite(SPRITE_PROBE)-1;
		}
		else if(entity.enemy.type == ROBOT) {
			width = entity.posX + width_sprite(SPRITE_ROBOT)-1;
		}
	}

	return width;
}

int posY_height_entity(entity_t entity) {
	int height = -1;

	if(entity.type == PLAYER) {
		height = entity.posY + height_sprite(SPRITE_PLAYER)-1;
	}
	else if(entity.type == ENEMY) {
		if(entity.enemy.type == PROBE) {
			height = entity.posY + height_sprite(SPRITE_PROBE)-1;
		}
		else if(entity.enemy.type == ROBOT) {
			height = entity.posY + height_sprite(SPRITE_ROBOT)-1;
		}
	}

	return height;
}