
#ifndef _DEVWDM_H
#define _DEVWDM_H
#endif
#define LONG long
//#define     WINAPI     __stdcall     
#define     APIENTRY     __stdcall 
#define     BOOL     bool 
#define     DWORD     long 
typedef enum
{
	AnalogVideo_None       = 0x00000000,
        AnalogVideo_NTSC_M     = 0x00000001, 
        AnalogVideo_PAL_B      = 0x00000010,
        AnalogVideo_PAL_D      = 0x00000020,
        AnalogVideo_SECAM_B    = 0x00001000,
        AnalogVideo_SECAM_D    = 0x00002000,
             
} AnalogVideoStandard;

/*devwdm_InitCard
�������ܣ�		��ʼ���豸
nID�� 			�豸ID�ţ�Ĭ��0
hWnd: 			��ʾ��Ƶ���ڵĴ��ھ��
nWidth, nHeight:	ͼ��ķֱ��� 
*/
LONG APIENTRY devwdm_InitCard(int nID, HWND hWnd, int nWidth, int nHeight);
/*devwdm_CloseCard:
�������ܣ�		�ر��豸
nID�� 			�豸ID��
*/
LONG APIENTRY devwdm_CloseCard(int nID);

/*devwdm_SetVideoStandard
�������ܣ�		������Ƶ��ʽ
nID�� 			�豸ID��
VideoStandard:		��ʽ,��P��:AnalogVideo_PAL_D;N��:AnalogVideo_NTSC_M��
*/
LONG APIENTRY devwdm_SetVideoStandard(int nID, LONG  VideoStandard);


/*devwdm_SaveBmpFile
�������ܣ�		���浥ǰ��֡ͼ��
nID�� 			�豸ID��
strFileName:		���bmp�ļ�������·����
*/
LONG APIENTRY devwdm_SaveBmpFile(int nID, char* strFileName);


/*devwdm_SetDisplayPos
�������ܣ�		������Ƶ������Ƶ���ڵ���ʾλ��
nID�� 			�豸ID��
x:			���Ͻǵ�xλ��
y:			���Ͻǵ�yλ��
w:			ͼ��Ŀ��
h:			ͼ��ĸ߶�
*/
LONG APIENTRY devwdm_SetDisplayPos(int nID, int x, int y, int w, int h);


/*devwdm_SetBrightNess,devwdm_SetContrast, devwdm_SetSaturation ,devwdm_SetHue
�������ܣ�		������Ƶ����ɫֵ,�ֱ�Ϊ���ȣ��Աȶȣ����Ͷ�ɫ��
nID�� 			�豸ID��
*/
LONG APIENTRY devwdm_SetBrightNess(int nID, LONG brightness);
LONG APIENTRY devwdm_SetContrast(int nID, LONG contrast);
LONG APIENTRY devwdm_SetSaturation(int nID, LONG satu);
LONG APIENTRY devwdm_SetHue(int nID, LONG hue);

/*devwdm_GetBrightNess,devwdm_GetContrast, devwdm_GetSaturation ,devwdm_GetHue
�������ܣ�		ȡ�õ�ǰ��Ƶ����ɫֵ,�ֱ�Ϊ���ȣ��Աȶȣ����Ͷ�ɫ��
nID�� 			�豸ID��
Min---Max:  ɫ�ʷ�Χֵ    
*/
LONG APIENTRY devwdm_GetBrightNess(int nID, LONG *brightness, LONG *Max, LONG *Min, LONG *Default);
LONG APIENTRY devwdm_GetContrast(int nID, LONG *contrast, LONG *Max, LONG *Min, LONG *Default);
LONG APIENTRY devwdm_GetSaturation(int nID, LONG *satu, LONG *Max, LONG *Min, LONG *Default);
LONG APIENTRY devwdm_GetHue(int nID, LONG *hue, LONG *Max, LONG *Min, LONG *Default);


/*devwdm_GetVideoPinCounts
�������ܣ�		ȡ�õ�ǰ�豸������Դ,�磺s-video, ������Ƶ��
nID�� 			�豸ID��
OutputPins: 		
InputPins		��ʱ����
*/
LONG APIENTRY devwdm_GetVideoPinCounts(int nID, LONG *OutputPins, LONG *InputPins);

/*devwdm_RouteOutPin
�������ܣ�		���õ�ǰ�豸������Դ,
nID�� 			�豸ID��
OutputPins: 		s-videoΪ0, ������ƵΪ1

*/
LONG APIENTRY devwdm_RouteOutPin(int nID, LONG OutputPin);


/*devwdm_StartVideoPreview
�������ܣ�		������Ƶ
nID�� 			�豸ID��

*/
LONG APIENTRY devwdm_StartVideoPreview(int nID);


/*devwdm_SetFlip
�������ܣ�		����Ƶͼ��ֱ��ת180��,
nID�� 			�豸ID��
dwFlip: 		ΪDWORD��ָ��,1��0, 1��ʾ��ת��0��ʾ������ʾ
fbGet:			1:�˺�����Getʹ�ã� 0���˺�����Setʹ��
*/

LONG APIENTRY devwdm_SetFlip(int nID, DWORD *dwFlip,  BOOL fbGet);


/*devwdm_SetMirror
�������ܣ�		����Ƶͼˮƽ��ת180��,
nID�� 			�豸ID��
dwFlip: 		ΪDWORD��ָ��,1��0, 1��ʾ��ת��0��ʾ������ʾ
fbGet:			1:�˺�����Getʹ�ã� 0���˺�����Setʹ��
*/
LONG APIENTRY devwdm_SetMirror(int nID, DWORD *dwMirror, BOOL fbGet);


/*devwdm_PreviewPause
�������ܣ�		��Ƶ��ͣ��ʾ,
nID�� 			�豸ID��
*/
LONG APIENTRY devwdm_PreviewPause(int nID);

/*devwdm_PreviewResume
�������ܣ�		����������Ƶ��ʾ,��devwdm_PreviewPause���Ӧ
nID�� 			�豸ID��
*/
LONG APIENTRY devwdm_PreviewResume(int nID);

/*devwdm_StartCaptureMp4
�������ܣ�		����¼�񣬽��ж�̬�ɼ�
nID�� 			�豸ID��
strFileName:		���¼���ļ�������·����
*/
LONG APIENTRY devwdm_StartCaptureMp4(int nID, char* strFileName);
/*devwdm_stopCaptureMp4
�������ܣ�		ֹͣ¼����ֹ���ж�̬�ɼ�
nID�� 			�豸ID��
*/
LONG APIENTRY devwdm_stopCaptureMp4(int nID);



