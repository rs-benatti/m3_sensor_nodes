/* res-leds.c */
#include "contiki.h"
#include <string.h>
#include "rest-engine.h"
#include "dev/light-sensor.h"
#include "dev/leds.h"

static void res_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset);

/* A simple getter example. Returns the reading from light sensor with a simple etag */
RESOURCE(res_leds,
         "title=\"Ambient light (supports JSON)\";rt=\"LightSensor\"",
         res_get_handler,
         NULL,
         NULL,
         NULL);

static void
res_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset)
{
  leds_off(LEDS_RED);
  REST.set_header_content_type(response, REST.type.TEXT_PLAIN);
  snprintf((char *)buffer, REST_MAX_CHUNK_SIZE, "LEDS STATE=%u", leds_get());
  REST.set_response_payload(response, (uint8_t *)buffer, strlen((char *)buffer));
}

