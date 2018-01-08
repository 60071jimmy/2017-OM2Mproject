#include <math.h>														//	include math.h header file, 引入標頭檔math.h
#include <stdbool.h>													//	include stdbool.h header file, 引入標頭檔stdbool.h
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>														//	include stdio.h header file, 引入標頭檔stdio.h
#include <stdlib.h>														//	include stdlib.h header file, 引入標頭檔stdlib.h
#include <string.h>														//	include string.h header file, 引入標頭檔string.h
#include <termios.h>
#include <unistd.h>

#define error_message printf

bool FileExistCheck(char *file_name)									//	FileExistCheck funtion implementation, FileExistCheck(檔案存在檢查)副程式
{																		//	start FileExistCheck funtion, 進入FileExistCheck(檔案存在檢查)副程式
	if( access( file_name, F_OK ) != -1 )								//	if file exist, 若檔案存在
	{																	//	entering if statement, 進入if敘述
    	return true;													//	return true, 傳回true
	} 																	//	ending if statement, 結束if敘述
	else 																//	if file doesn't exist, 若檔案不存在
	{																	//	entering else statement, 進入else敘述
	    return false;													//	return false, 回傳false
	}																	//	ending else statement, 結束else敘述
} 																		//	FileExistCheck funtion end, 結束FileExistCheck(檔案存在檢查)副程式
bool FileReadPermissionCheck(const char *file_name)						//	FileReadPermissionCheck funtion implementation, FileReadPermissionCheck(檔案讀取權限檢查)副程式
{																		//	start FileReadPermissionCheck funtion, 進入FileReadPermissionCheck(檔案讀取權限檢查)副程式
	if( access( file_name, R_OK ) != -1 )								//	if the file which path is file_name is readable, 若檔案可讀取
	{																	//	entering if statement, 進入if敘述
    	return true;													//	return true, 傳回true
	} 																	//	ending if statement, 結束if敘述
	else 																//	if the file which path is file_name isn't readable, 若檔案不可讀取
	{																	//	entering else statement, 進入else敘述
		return false;													//	return false, 回傳false
	}																	//	ending else statement, 結束else敘述
} 																		//	FileReadPermissionCheck funtion end, 結束FileReadPermissionCheck(檔案讀取權限檢查)副程式
bool FileWritePermissionCheck(const char *file_name)					//	FileWritePermissionCheck funtion implementation, FileWritePermissionCheck(檔案寫入權限檢查)副程式
{																		//	start FileWritePermissionCheck funtion, 進入FileWritePermissionCheck(檔案寫入權限檢查)副程式
	if( access( file_name, W_OK ) != -1 )								//	if the file which path is file_name is writable, 若檔案可寫入
	{																	//	entering if statement, 進入if敘述
    	return true;													//	return true, 傳回true
	} 																	//	ending if statement, 結束if敘述
	else 																//	if the file which path is file_name isn't writable, 若檔案不可寫入
	{																	//	entering else statement, 進入else敘述
	    return false;													//	return false, 回傳false
	}																	//	ending else statement, 結束else敘述
} 																		//	ending FileWritePermissionCheck funtion, 結束FileWritePermissionCheck(檔案寫入權限檢查)副程式

/*	FileWrite function, FileWrite(檔案寫入)副程式
	Implementation of text file writing.
	執行文字檔案寫入
	file_name為欲寫入檔案檔名
	input_str為欲寫入檔案之指標形式字串資料
	mode為寫入檔案模式設定，可傳入"w"或"a"，"w"為新增/覆蓋模式，"a"為擴充模式
	回傳結果：若檔案寫入成功回傳true，若寫入失敗回傳false
 */
bool FileWrite(const char *file_name, const char *input_str, const char *mode)
//	FileWrite funtion implementation,
{																		//	start FileWrite funtion, 進入FileWrite(檔案寫入)副程式
	FILE *file_point;													//	宣告一file_point指標，控制檔案讀寫
	if (strcmp(mode, "w") != 0 && strcmp(mode, "a") != 0 && strcmp(mode, "w+") != 0 && strcmp(mode, "a+") != 0)
	//	若mode參數不為"w"亦不為"a"亦不為"w+"亦不為"a+"
	{																	//	entering if statement, 進入if敘述
		printf("FileWrite:mode ERROR!\n");								//	Show "FileWrite:mode ERROR!" and line feed, 顯示"FileWrite:mode ERROR!"並換行
		return false;													//	return false and exit funtion, 回傳false並結束副程式返回
	}																	//	ending if statement, 結束if敘述
	if( strcmp(mode, "a") == 0 || strcmp(mode, "a+") == 0 )				//	If mode setting is "a" or "a+", 若mode參數為"a"或"a+"(擴充模式)
	{																	//	entering if statement, 進入if敘述
		if (FileWritePermissionCheck(file_name) == false)				//	if the file which path is file_name isn't writable, 若檔案無法寫入
		{																//	entering if statement, 進入if敘述
			printf("FileWrite:permission ERROR!\n");					//	顯示"FileWrite:permission ERROR!"並換行
			return false;												//	return false and exit funtion, 回傳false並結束副程式返回
		}																//	ending if statement, 結束if敘述
	}																	//	ending if statement, 結束if敘述
	file_point = fopen(file_name, mode);								//	Use input variable "mode" to open file which path is file_name, 以mode模式打開檔案
	//	fprintf或fputs語法二擇一使用
	fprintf(file_point, input_str);										//	以fprintf語法寫入檔案
	//fputs(input_str, file_point);										//	以fputs語法寫入檔案
	fclose(file_point); 												//	關閉檔案
	return true;														//	回傳true並結束副程式返回
}																		//	ending FileWrite funtion, 結束FileWrite(檔案寫入)副程式


int
set_interface_attribs (int fd, int speed, int parity)
{
        struct termios tty;
        memset (&tty, 0, sizeof tty);
        if (tcgetattr (fd, &tty) != 0)
        {
                error_message ("error %d from tcgetattr", errno);
                return -1;
        }

        cfsetospeed (&tty, speed);
        cfsetispeed (&tty, speed);

        tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
        // disable IGNBRK for mismatched speed tests; otherwise receive break
        // as \000 chars
        tty.c_iflag &= ~IGNBRK;         // disable break processing
        tty.c_lflag = 0;                // no signaling chars, no echo,
                                        // no canonical processing
        tty.c_oflag = 0;                // no remapping, no delays
        tty.c_cc[VMIN]  = 0;            // read doesn't block
        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

        tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

        tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
                                        // enable reading
        tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
        tty.c_cflag |= parity;
        tty.c_cflag &= ~CSTOPB;
        tty.c_cflag &= ~CRTSCTS;

        if (tcsetattr (fd, TCSANOW, &tty) != 0)
        {
                error_message ("error %d from tcsetattr", errno);
                return -1;
        }
        return 0;
}

void
set_blocking (int fd, int should_block)
{
        struct termios tty;
        memset (&tty, 0, sizeof tty);
        if (tcgetattr (fd, &tty) != 0)
        {
                error_message ("error %d from tggetattr", errno);
                return;
        }

        tty.c_cc[VMIN]  = should_block ? 1 : 0;
        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

        if (tcsetattr (fd, TCSANOW, &tty) != 0)
                error_message ("error %d setting term attributes", errno);
}


int main(void)
{
	char *portname = "/dev/ttyACM0";

	int fd = open (portname, O_RDWR | O_NOCTTY | O_SYNC);
	if (fd < 0)
	{
		error_message ("error %d opening %s: %s", errno, portname, strerror (errno));
		return;
	}

	set_interface_attribs (fd, B115200, 0);  // set speed to 115,200 bps, 8n1 (no parity)
	set_blocking (fd, 0);                // set no blocking

	//write (fd, "hello!\n", 7);           // send 7 character greeting

	usleep ((7 + 25) * 100);             // sleep enough to transmit the 7 plus
		                             // receive 25:  approx 100 uS per char transmit
	char buf[100] = {0};
	while(1)
	{
		int n = read (fd, buf, sizeof buf);  // read up to 100 characters if ready to read
		printf("%s", buf);
		FileWrite("data.txt", "<om2m:cin xmlns:om2m=\"http://www.onem2m.org/xml/protocols\"><cnf>message</cnf><con>", "w");
		FileWrite("data.txt", buf, "a");
		FileWrite("data.txt", "</con></om2m:cin>", "a");
		system("curl -v -i -H \"X-M2M-Origin: admin:admin\" -H \"Content-Type: application/xml;ty=4\" -d @data.txt -X POST http://192.168.0.118:8080/~/mn-cse/mn-name/MY_SENSOR/DATA");
		sleep (10);
	}
}
