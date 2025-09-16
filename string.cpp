#include <stdio.h>
#include <stdint.h>

#include "asserts.h"
#include "logger.h"
#include "test_part.h"
#include "input.h"
#include "string.h"

const size_t STANDART_CALLOC_SIZE = 120;
const float GROW_FACTOR = 2;
int main() {
	logger_initialize_stream(NULL); 
	char str1[] = "12345";
	char str2[] = "543210";
	strncpy(str1, str2, 7);
	LOGGER_DEBUG("ALL OK");
	printf("%s", str1); 
	char str3[5] = {};
	fgets(str3, 5, stdin);
	printf("%s", str3);
}

ssize_t my_getline(char **lineptr, size_t *size_of_buffer, FILE *stream) { //TODO: ДОбавить к названиям функций my
    LOGGER_DEBUG("my_getline started");
    hard_assert(lineptr != nullptr, "Pointer to string is nullptr"); //TODO: Большими буквами
    hard_assert(stream != nullptr, "stream is nullptr");

    int ch = 0;
    size_t curr_size = *size_of_buffer;
    size_t num_chars = 0;
    bool is_malloc_used = false;

    if (*lineptr == nullptr) {
        curr_size = STANDART_CALLOC_SIZE;
        LOGGER_DEBUG("Memory allocation started, trying to malloc %ld bytes", curr_size);
        *lineptr = (char*)calloc(curr_size, sizeof(**lineptr));
        if (*lineptr == nullptr) return -1;
        is_malloc_used = true;
        *size_of_buffer = curr_size;
    }

    char *ptr = *lineptr; //TODO: Изменить нащвание

    while ((ch = getc(stream)) != EOF) {
        if (num_chars + 1 >= curr_size) { //TODO: Вынести в отдельную функцию
            curr_size *= GROW_FACTOR;
            LOGGER_DEBUG("Memory reallocation started, trying to realloc %ld bytes", curr_size);
            char *new_ptr = (char *)realloc(*lineptr, curr_size); //TODO: Recalloc realize
            if (new_ptr == nullptr) {
            	if (is_malloc_used) free(*lineptr);
            	return -1;
            }
            *lineptr = new_ptr;
            ptr = *lineptr + num_chars; 
            *size_of_buffer = curr_size;
        }

        *ptr++ = (char)ch;
        num_chars++;

        if (ch == '\n') break; //Для этого
    }

    if (num_chars == 0 && ch == EOF) {
    	if (is_malloc_used) free(*lineptr);
    	return -1;
    }

    *ptr = '\0'; //С помощью новой функции сделать проверку на выход за границы массивы
    return num_chars;
}

char* strdup(const char *str) {
	LOGGER_DEBUG("strdup started");
	hard_assert(str != nullptr, "str is nullptr");

	char* dupplicate = (char*)calloc((strlen(str) + 1), sizeof(*str));
	strcpy(dupplicate, str);
	return dupplicate;
}

char* fgets(char *str, int num_chars, FILE *stream) {
	LOGGER_DEBUG("strcat started");
	hard_assert(str != nullptr, "str is nullptr");
	hard_assert(stream != nullptr, "stream is nullptr");

	int ch = 0;
	while ((ch = getc(stream)) != EOF &&
		   ch != '\n' && 
		   num_chars > 1) {
		num_chars--;
		*(str++) = ch;
	}
	*(str++) = '\0';
	if (ferror(stream)) return NULL;
	return str;
}

char* strncat(char* destin, const char* source, size_t num) {
	LOGGER_DEBUG("strcat started");
	hard_assert(destin != nullptr, "destination is nullptr");
	hard_assert(source != nullptr, "source is nullptr");

	char* start_ptr = destin;
	while (*destin != '\0') destin++;

	while (*source != '\0' && num > 0) {
		num--;
		*(destin++) = *(source++);
	}
	return start_ptr;
}


char* strcat(char* destin, const char* source) {
	return strncat(destin, source, SIZE_MAX);
}


char* strncpy(char* destin, const char* source, size_t num) {
	LOGGER_DEBUG("strncpy started");
	hard_assert(destin != nullptr, "destination is nullptr");
	hard_assert(source != nullptr, "source is nullptr");

	char *start_prt = destin;
	while (*source != '\0' && num > 0) {
		*(destin++) = *(source++);
		num--;
	}
	return start_ptr;
}


char* strcpy(char* destin, const char* source) {
	return strncpy(destin, source, SIZE_MAX);
}

size_t strlen(const char* str) {
	LOGGER_DEBUG("strlen started");
	hard_assert(str != nullptr, "str is nullptr");

	size_t cnt = 0; 
	while (*str != '\0') {
		cnt++;
		str++;
	}
	return cnt;
}
//TODO: НАписать комент про каст const в noconst 
char* strchr(const char* str, char ch) { //Почему в оригинале no const
	LOGGER_DEBUG("strchr started");
	hard_assert(str != nullptr, "str is nullptr");
	
	while(*str != '\0') {
		if(*(str++) == ch) return (char*)str;
	}

	LOGGER_WARNING("%c not found", ch);
	return NULL;
}

int puts(const char* str) {
	LOGGER_DEBUG("puts started");
	hard_assert(str != nullptr, "str is nullptr");

	while (*str != '\0') {
		if(putchar(*str++) == EOF) return EOF;
	}
	return (putchar('\n') == EOF) ? EOF : 1;
}


