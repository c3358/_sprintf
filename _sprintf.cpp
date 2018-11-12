#include "_sprintf.h"
#include <string>
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>

#ifndef va_copy
#define va_copy(dst, src) memcpy(&(dst), &(src), sizeof(va_list))
#endif

/************************************************************************
* @brief ����ת�ַ���
* @param[in] ����
* @param[out] �ַ���
* @return �����ַ�������
************************************************************************/
int _itoa(int num, char buf[32])
{
	static const char s[] = "0123456789";
	int n = num;
	char *dst = buf;
	if (n < 0) { *dst++ = '-'; n = -n; }
	if (n < 10)
	{
		*dst++ = s[n]; *dst = 0;
	}else
	{
		char tmp[32], *p = tmp;
		while (n) { *p++ = s[n % 10]; n /= 10; }
		while (--p != tmp) *dst++ = *p;
		*dst++ = *tmp; *dst = 0;
	}
	return dst-buf;
}

/************************************************************************
* @brief ������ת�ַ���
* @param[in] ������
* @param[out] �ַ���
* @param[in] ����(С��λ)
* @return �����ַ�������
************************************************************************/
int _ftoa(double val, char buf[32], int eps)
{
	double f = val;
	char *p = buf;
	if (val < 0) { *p++ = '-'; f = -f; }
	int n = f;
	int len = _itoa(n, p);
	return len + __ftoa(f - n, p + len, eps);
}

/************************************************************************
* @brief ������ת�ַ�������Χ(-1, 1)
* @param[in] ������
* @param[out] �ַ���
* @param[in] ����(С��λ)
* @return �����ַ�������
************************************************************************/
int __ftoa(double val, char buf[32], int eps)
{
	double f = val;
	char *p = buf;
	assert(-1.0 < f && f < 1.0 && eps > 0);
	static const char s[] = "0123456789";
	if (f<0){*p++ = '-'; f = -f;}*p++ = '.';
	for (int i = eps+1, n; --i; ++p, f -= n)
		*p = s[n = f *= 10.0];
	*p = 0;
	return p-buf;
}

/************************************************************************
* @brief �滻sprintf
* @ref �ɱ䳤�����б����������塪��va_arg���ɽ��ܵ�����
* http://www.cppblog.com/ownwaterloo/archive/2009/04/21/80655.aspx
************************************************************************/
int _sprintf(char *dst, const char *format, ...)
{
	char *s = dst;
	const char *f = format;
	va_list ap, another;
	va_start(ap, format);
	va_copy(another, ap);
	while (*f)
	{
		int n = 1;
		if ('%' != *f)
		{
			*s = *f;
		}else{
			++f;
			switch (*f)
			{
			case 's':// �ַ���
				{
					const char *p = va_arg(ap, char*);
					n = strlen(p);
					memcpy(s, p, n);
				}
				break;

			case 'd':// ����
				{
					int i = va_arg(ap, int);
					char buf[32];
					n = _itoa(i, buf);
					memcpy(s, buf, n);
				}
				break;

			case 'f':// ������
				{
					double v = va_arg(ap, double);
					char buf[32];
					n = _ftoa(v, buf);
					memcpy(s, buf, n);
				}
				break;

			case 'c':// �ַ�
				{
					*s = va_arg(ap, int);
				}
				break;

			default:
				{
					assert(0);
					va_end(ap);
					int x = vsprintf(dst, format, another);
					va_end(another);
					return x;
				}
				break;
			}
		}
		++f;
		s += n;
	}
	*s = 0;
	va_end(ap);
	return s-dst;
}
