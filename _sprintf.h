#pragma once

// ����ת�ַ���
int _itoa(int num, char buf[32]);

// ����ת�ַ���
int _ftoa(double val, char buf[32], int eps= 6);

// ����ת�ַ�������Χ��-1��1��
int __ftoa(double val, char buf[32], int eps= 6);

// ���sprintf
int _sprintf(char *dst, const char *format, ...);
