#pragma once

// ����ת�ַ���
inline int _itoa(int num, char buf[32]);

int _i2a(int num, char buf[32], int radix= 10);

// ����ת�ַ���
int _ftoa(double val, char buf[32], int eps= 6);

// ����ת�ַ�������Χ��-1��1��
int __ftoa(double val, char buf[32], int eps= 6);

// ���sprintf
int _sprintf(char *dst, const char *format, ...);
