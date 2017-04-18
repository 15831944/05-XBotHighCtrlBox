#ifndef JOYSTICK_H

#define JOYSTICK_H
 
 
#include <QLibrary> 
 
#ifdef Q_WS_WIN 
#include "windows.h" 
#include "w32api.h" 
#include "winuser.h" 
#include "mmsystem.h" 
 
//joyGetDevCaps ��ѯָ������Ϸ���豸��ȷ��������
//joyGetNumDevs ����ϵͳ֧�ֵ���Ϸ���豸������
//joyGetPos ��ѯָ������Ϸ���豸��λ�úͻ��
//joyGetPosEx ��ѯһ����Ϸ���豸��λ�ú����İ�Ť״̬
//joyGetThreshold ��ѯָ������Ϸ���豸�ĵ�ǰ�ƶ���ֵ
//joyReleaseCapture �ͷ���JoySetCapture�������õ���ָ����Ϸ���豸�ϵĲ���
//joySetCapture ����һ����Ϸ����Ϣ��ָ���Ĵ���
//joySetThreshold ����ָ������Ϸ���豸���ƶ���ֵ
 
//���ض�ý��� 
 QLibrary mylib("Winmm.dll"); 
 //������Ϸ�˲�����joySetCapture 
 typedef int (*MyPrototype) (HWND, UINT, UINT, BOOL); 
 MyPrototype qJoySetCapture = (MyPrototype)mylib.resolve("joySetCapture"); 
 //��Ϸ������ú��� 
 typedef void (*MyPrototype1) (UINT); 
 MyPrototype1 qJoyReleaseCapture = (MyPrototype1)mylib.resolve("joyReleaseCapture"); 
 //������Ϸ��λ�ü���ť����� 
 typedef void (*MyPrototype2) (UINT, LPJOYINFOEX); 
 MyPrototype2 qJoyGetPosEx = (MyPrototype2)mylib.resolve("joyGetPosEx"); 
 //������Ϸ��λ�ü���ť����� 
 typedef void (*MyPrototype0) (UINT, LPJOYINFO); 
 MyPrototype0 qJoyGetPos = (MyPrototype0)mylib.resolve("joyGetPos"); 
 //��ȡ���ݸ��ƶ���ֵ 
 typedef void (*MyPrototype3) (UINT, LPUINT); 
 MyPrototype3 qJoyGetThreshold = (MyPrototype3)mylib.resolve("joyGetThreshold"); 
 //��ȡ���ݸ�������Ϣ���Խṹ��JoyCaps���� 
 typedef void (*MyPrototype4) (UINT, LPJOYCAPS, UINT); 
 MyPrototype4 qJoyGetDevCaps = (MyPrototype4)mylib.resolve("joyGetDevCapsW"); 
 //�ж��ٸ���Ϸ�˿����� 
 typedef UINT (*MyPrototype5) (void); 
 MyPrototype5 qJoyGetNumDevs = (MyPrototype5)mylib.resolve("joyGetNumDevs"); 
 
 
 #endif 
 
#endif // JOYSTICK_H 
