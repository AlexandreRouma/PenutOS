
/* La fonction memcopy permet de copier n octets de src vers dest.
 * Les adresses sont lineaires.
 */
void *memcpy(char *dst, char *src, int n)
{
	char *p = dst;
	while (n--)
		*dst++ = *src++;
	return p;
}
