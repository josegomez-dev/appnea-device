#include "JsonXYZ.h"

void jsonInit(String *json){
	json->concat("{");
}

void jsonClose(String *json){
	json->setCharAt(json->length()-1, '}');
}

void jsonClear(String *json){
	json->remove(0);
}

void addToJson(String *json, String id, String value){
	json->concat("\"");
	json->concat(id);
	json->concat("\":");
	json->concat("\"");
	json->concat(value);
	json->concat("\"");
	json->concat(",");
}

void addToJsonAux(String *json, String id, String value){
	json->concat("\"");
	json->concat(id);
	json->concat("\":");
	json->concat(value);
	json->concat(",");
}

void addToJson(String *json, String id, int value){
	addToJsonAux(json, id, String(value));
}

void addToJson(String *json, String id, float value){
	addToJsonAux(json, id, String(value));
}

String getJsonStr(String input, String attribute) {
	String value = "";
	int start = input.indexOf(":",input.indexOf(attribute));
	int end = input.indexOf(",",start);
	int end2 = input.indexOf("}",start);
	if (end == -1){end = end2;}
	for (int n = start+1; n<end; n++) {
		value.concat(input[n]);
	}
	int str_type = value.indexOf('\"');
	if(str_type != -1){
		value.remove(str_type, 1);
		value.remove(value.length()-1);
	}
	return value;               
}

int getJsonInt(String input, String attribute) {
	String value = getJsonStr(input, attribute);
	return value.toInt();
}

float getJsonFloat(String input, String attribute) {
	String value = getJsonStr(input, attribute);
	return value.toFloat();
}