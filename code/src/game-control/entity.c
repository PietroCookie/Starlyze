#include "entity.h"

void initialise_entity(entity_t *entity, type_sprite_enum type, int posX, int posY) {
	entity->type = type;
	entity->posX = posX;
	entity->posY = posY;
	entity->freeze = 0;
}