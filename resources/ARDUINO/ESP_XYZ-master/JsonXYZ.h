#include <Arduino.h>

#ifndef JSON_XYZ
#define JSON_XYZ


void jsonInit(String *json);

void jsonClose(String *json);

void jsonClear(String *json);

void addToJson(String *json, String id, String value);

void addToJsonAux(String *json, String id, String value);

void addToJson(String *json, String id, int value);

void addToJson(String *json, String id, float value);

String getJsonStr(String input, String attribute);

int getJsonInt(String input, String attribute);

float getJsonFloat(String input, String attribute);

#endif
