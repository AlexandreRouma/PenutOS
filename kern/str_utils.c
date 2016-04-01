#include "str_utils.h"

int atoi(char *str)
{
    int res = 0; // Initialize result
	int i = 0;
	
	while (str[i] != '\0'){
		res = res*10 + str[i] - '0';
		i = i + 1;
	}
  
    // return result.
    return res;
}

char* itoa(int n)
{
	char* s = "";
    int i, sign;

    if ((sign = n) < 0)  /* record sign */
        n = -n;          /* make n positive */
    i = 0;
    do {       /* generate digits in reverse order */
        s[i++] = n % 10 + '0';   /* get next digit */
    } while ((n /= 10) > 0);     /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
	n = 0;
	return s;
}

int strlen(const char* str) {
	int ret = 0;
	while ( str[ret] != 0 )
		ret++;
	return ret;
}

void reverse(char s[])
{
    int i, j;
    char c;

    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

char* append(char* s, char c)
{
    int len = strlen(s);
    s[len] = c;
	s[len + 1] = '\0';
	return s;
}

int cmpac(char chars[40], char* string){
	int ret = 1;
	int len = strlen(string) + 1;
	int i = 0;
	
	while (i < len){
		if (chars[i] == string[i]){
			
		}
		else{
			ret = 0;
			goto stop1;
		}
		i++;
	}
stop1:
	return ret;
}

int indexOf(char* string, char c){
	int i = 0;
	int ret = 0;
	int length = strlen(string);
	while (i < length){
		if (string[i] == c){
			ret = i;
			goto stop2;
		}
		else{
			
		}
		i++;
	}
stop2:
    return ret;
}

char* substring(char* string, int start, int end){
	char* ret = "";
	int i = 0;
	end++;
	while (start < end){
		ret[i] = string[start];
		start++;
		i++;
	}
	return ret;
}

int prefix(const char *pre, const char *str)
{
    char cp;
    char cs;

    if (!*pre)
        return 1;

    while ((cp = *pre++) && (cs = *str++))
    {
        if (cp != cs)
            return 0;
    }

    if (!cs)
        return 0;

    return 1;
}