#include "Resource.h"


#include "../protocol/common.h"
#include "../protocol/const.h"
#include "../protocol/protocol.h"

#include "NetworkManager.h"
#include "ObjectManager.h"
#include <fstream>

// console
//#ifdef _DEBUG
//#pragma comment(linker, "⁄entry:WinMainCRTStartup ⁄subsystem:console")
//#endif
#ifdef _DEBUG
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#endif


#define MAX_LOADSTRING 100



HWND g_Hwnd = NULL;
RECT gMap;
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HDC		dc;


CS::NetworkManager* netMgr	= nullptr;
CS::ObjectManager* ObjMar	= nullptr;


// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.
	AllocConsole();
	freopen("CONOUT$", "wt", stdout);




	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_MY20180919, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }





    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY20180919));

    MSG msg;

    // 기본 메시지 루프입니다.
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }


    return (int) msg.wParam;
}




ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY20180919));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY20180919);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      400, 400, 1024, 1024, nullptr, nullptr, hInstance, nullptr);
  


   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}



const int BlockCnt		{ 20 };  // 블럭 칸수
char buf[1024]		{ "hihi" }; 
POINT g_block			{ 0 };

PLAYER_OBJ_POS player[2] {0};
std::ofstream out;

CS::Sync sync(player);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
     switch (message)
    {

	case WM_CREATE:

		g_Hwnd = hWnd;
		GetClientRect(g_Hwnd, &gMap);


		netMgr = new CS::NetworkManager;
		ObjMar = new CS::ObjectManager(&sync);


		netMgr->Initialize();

		printf_s("Start Network %p \n ", netMgr);
		netMgr->CreateThread();


		break;
//
//	
//			receved = recv(wParam, buf, BUFSIZE, 0);
//			
//			memcpy(&temp, buf, sizeof(Packet));
//
//			printf_s("Receved %d Bytes ",receved);
//		
//			if ( temp.s_type == Move )
//			{
//				memcpy(&mtemp, buf, sizeof(MovePacket));
//				printf_s("Move (%d, %d)", mtemp.s_X,mtemp.s_Y );
//
//				g_Player[mtemp.dwId].SetPos( mtemp.s_X, mtemp.s_Y);
//				out <<  "Normal! WM_SOCKET::FD_READ::MOVE " << mId << "X "<< mtemp.s_X << "Y "<<  mtemp.s_X << //				std::endl;
//			}
//			else if( temp.s_type == Connect )
//			{
//				memcpy(&ctemp, buf, sizeof(ConnectPacket));
//				printf_s( "Connect receved ID : %d" , ctemp.s_id);
//				mId = ctemp.s_id;
//				out << "Normal! WM_SOCKET::FD_READ::Connect mId : " << mId << std::endl;
//				g_Player[mId].SetPos(1, 1);
//
//			}
//			else if (temp.s_type == DisConnect)
//			{
//				memcpy(&ctemp, buf, sizeof(DisConnectPacket));
//				printf_s("DisConnect receved ID : %d", ctemp.s_id);
//				mId = ctemp.s_id;
//				out << "Normal! WM_SOCKET::FD_READ::DisConnect mId : " << mId << std::endl;
//				g_Player[mId].SetPos(-1,-1);
//			}
//			else
//			{
//				printf(" else ");
//				out << "Error! WM_SOCKET::FD_READ::Connect "<< std::endl;
//			}
//			printf(" READ : %s", buf);
//
//			InvalidateRect(g_Hwnd,NULL,TRUE);
//			break;
//		}
//
//		break;

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다.
            switch (wmId)
            {

            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

	case WM_KEYDOWN:
		switch (wParam)
		{  
		case VK_UP:
			netMgr->OnSend();
			break;
		case VK_DOWN:
			netMgr->OnSend();
			break;

		case VK_LEFT:
			netMgr->OnSend();
			break;

		case VK_RIGHT:
			netMgr->OnSend();
			/*mtemp.s_length = sizeof(MovePacket);
			mtemp.dwId = mId;
			mtemp.s_type = Move;
			mtemp.s_X = g_Player[mId].GetPosX() +1;
			mtemp.s_Y = g_Player[mId].GetPosY();
			send(listenSocket, (char*)&mtemp, sizeof(MovePacket), 0);*/
			break;

		default:
			break;
		}
		//InvalidateRect(hWnd, NULL, TRUE);
		break;

    case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다.
		//DrawMap(hdc, gMap.right, gMap.bottom, BlockCnt, BlockCnt);

		EndPaint(hWnd, &ps);
		break;
	}

    case WM_DESTROY:
			printf_s("End Server");
			netMgr->Finalize();
			out.close();
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

