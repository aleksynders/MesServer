#define _CRT_SECURE_NO_WARNINGS
#define SIZE_BUFFER 140

#include <stdio.h>
#include <Windows.h>

int main()
{
	system("chcp 1251>null");
	LPSTR lpszPipiName = L"\\\\.\\pipe\\MyPipe";

	HANDLE hNamePipe;
	DWORD size_buffer = SIZE_BUFFER;
	LPWSTR buffer = (CHAR*)calloc(size_buffer, sizeof(CHAR));
	char message[SIZE_BUFFER];
	BOOL Connected;
	DWORD actual_readen;
	BOOL SeccessRead;
	while (TRUE)
	{
		hNamePipe = CreateNamedPipe(
			lpszPipiName,
			PIPE_ACCESS_DUPLEX,
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
			PIPE_UNLIMITED_INSTANCES,
			SIZE_BUFFER,
			SIZE_BUFFER,
			INFINITE,
			NULL);
		Connected = ConnectNamedPipe(hNamePipe, NULL);
		if (Connected)
		{
			SeccessRead = ReadFile(hNamePipe, buffer, size_buffer, &actual_readen, NULL);
			if (SeccessRead)
			{
				printf("Сообщение: ");
				printf(buffer);
				printf("\nВведите сообщение для клиента: ");
				gets(message);
				buffer = &message;
				WriteFile(hNamePipe, buffer, size_buffer, &actual_readen, NULL);


				//printf("\nПолученное число: ");
				//printf(buffer);
				//printf("\n");
				//float chislo = atof(buffer);
				//chislo *= chislo;
				//if(chislo != 0)
				//	sprintf(message, "Возведенное число в квадрат = %g", chislo);
				//else
				//	sprintf(message, "Не корректные данные!");
				//buffer = &message;
				//printf(buffer);
				//WriteFile(hNamePipe, buffer, size_buffer, &actual_readen, NULL);
			}
		}
		CloseHandle(hNamePipe);
	}
}