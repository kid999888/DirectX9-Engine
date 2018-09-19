//=================================================================================================
//                                                        
//　　　DebugGUIクラスプログラム[DebugGUI.cpp]
//      Author:王暁晨(AT-13A-281 04)　2018.06.13      
//                                                        
//=================================================================================================
#if defined(DEBUG)
//=================================================================================================
//　　　ヘッダファイル           
//=================================================================================================
#include "DebugGUI.h"
#include "Mode.h"
#include "Motion.h"

//=================================================================================================
//　　　実体定義
//=================================================================================================
bool CDebugGUI::m_bshow_demo_window = false;
bool CDebugGUI::m_bshow_Motion_window = false;
CPlayer* CDebugGUI::m_pPlayer = nullptr;
CCamera* CDebugGUI::m_pCamera = nullptr;
CField* CDebugGUI::m_pField = nullptr;

//=================================================================================================
//　　　DebugGUIクラス初期処理         
//=================================================================================================
bool CDebugGUI::Init(void)
{
	//ImGUI処理
	m_bshow_demo_window = false;
	m_bshow_Motion_window = false;

	return true;
}

//=================================================================================================
//　　　DebugGUIウィンドウズ更新処理
//=================================================================================================
void CDebugGUI::UpdateWindow(void)
{
	ImGui_ImplDX9_NewFrame();

	// 1. Show a simple window.
	// Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets automatically appears in a window called "Debug".
	{
		ImGui::Text("Average and FPS:");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate); 

		ImGui::Text("Mouse Position:");
		ImGui::SameLine();
		ImGui::Text("(%f,%f)", (float)CInputMouse::GetPosWorld()->x, (float)CInputMouse::GetPosWorld()->y);

		ImGui::Text("User Screen Mouse Position:");
		ImGui::SameLine();
		ImGui::Text("(%f,%f)", (float)CInputMouse::GetPosUserScreen()->x, (float)CInputMouse::GetPosUserScreen()->y);

		switch (CManager::GetMode()->GetModeId())
		{
		case MODE_TITLE:
			ImGui::Text("Camera Position:");
			ImGui::SameLine();
			ImGui::Text("(%f,%f,%f)", m_pCamera->GetCameraPos().x, m_pCamera->GetCameraPos().y, m_pCamera->GetCameraPos().z);

			ImGui::Text("Camera At Position:");
			ImGui::SameLine();
			ImGui::Text("(%f,%f,%f)", m_pCamera->GetCameraAtPos().x, m_pCamera->GetCameraAtPos().y, m_pCamera->GetCameraAtPos().z);
			break;
		case MODE_GAME:
			ImGui::Text("Camera Position:");
			ImGui::SameLine();
			ImGui::Text("(%f,%f,%f)", m_pCamera->GetCameraPos().x, m_pCamera->GetCameraPos().y, m_pCamera->GetCameraPos().z);

			ImGui::Text("Camera At Position:");
			ImGui::SameLine();
			ImGui::Text("(%f,%f,%f)", m_pCamera->GetCameraAtPos().x, m_pCamera->GetCameraAtPos().y, m_pCamera->GetCameraAtPos().z);

			ImGui::Text("Player Position:");
			ImGui::SameLine();
			ImGui::Text("(%f,%f,%f)", CPlayer::GetPlayerPos().x, CPlayer::GetPlayerPos().y, CPlayer::GetPlayerPos().z);

			ImGui::Text("Player Rotation:");
			ImGui::SameLine();
			ImGui::Text("(%f,%f,%f)", m_pPlayer->GetRotationX(), m_pPlayer->GetRotationY(), m_pPlayer->GetRotationZ());

			ImGui::Text("Player At Position:");
			ImGui::SameLine();
			ImGui::Text("(%f,%f,%f)", m_pPlayer->GetPlayerFront().x, m_pPlayer->GetPlayerFront().y, m_pPlayer->GetPlayerFront().z);
			break;
		case MODE_RESULT:
			ImGui::Text("Camera Position:");
			ImGui::SameLine();
			ImGui::Text("(%f,%f,%f)", m_pCamera->GetCameraPos().x, m_pCamera->GetCameraPos().y, m_pCamera->GetCameraPos().z);

			ImGui::Text("Camera At Position:");
			ImGui::SameLine();
			ImGui::Text("(%f,%f,%f)", m_pCamera->GetCameraAtPos().x, m_pCamera->GetCameraAtPos().y, m_pCamera->GetCameraAtPos().z);
			break;
		case MODE_GAMEOVER:
			break;
		case MODE_TRAINING:
			break;
		case MODE_MOTION_EDITING:
			ImGui::Text("Camera Position:");
			ImGui::SameLine();
			ImGui::Text("(%f,%f,%f)", m_pCamera->GetCameraPos().x, m_pCamera->GetCameraPos().y, m_pCamera->GetCameraPos().z);

			ImGui::Text("Camera At Position:");
			ImGui::SameLine();
			ImGui::Text("(%f,%f,%f)", m_pCamera->GetCameraAtPos().x, m_pCamera->GetCameraAtPos().y, m_pCamera->GetCameraAtPos().z);

			ImGui::Checkbox("Motion Editing Window", &m_bshow_Motion_window);


			if (m_bshow_Motion_window)
			{
				ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.0f, 0.7f, 0.2f, 1.0f));
				ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.0f, 0.3f, 0.1f, 1.0f));
				ImGui::SetNextWindowPos(ImVec2(860, 20), ImGuiSetCond_Once);
				ImGui::SetNextWindowSize(ImVec2(400, 600), ImGuiSetCond_Once);
				ImGui::Begin("Motion Editing Window", &m_bshow_Motion_window);

				for (int nCount = 0;nCount < 10;nCount++)
				{
					ImGui::Text("Part[%d]", nCount);
					ImGui::Text("Position:");
					ImGui::SameLine();
					ImGui::Text("(%f,%f,%f)", CMotion::GetPart(nCount).Position.x, CMotion::GetPart(nCount).Position.y, CMotion::GetPart(nCount).Position.z);
					ImGui::Text("Rotation:");
					ImGui::SameLine();
					ImGui::Text("(%f,%f,%f)", CMotion::GetPart(nCount).Rotation.x, CMotion::GetPart(nCount).Rotation.y, CMotion::GetPart(nCount).Rotation.z);
				}

				if (ImGui::Button("Close Me"))
					m_bshow_Motion_window = false;
				ImGui::End();

				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
			}
			break;
		default:
			break;
		}
		
		ImGui::Checkbox("Demo Window", &m_bshow_demo_window);      // Edit bools storing our windows open/close state
		
	}

	// 2. Show another simple window. In most cases you will use an explicit Begin/End pair to name your windows.
	/*if (show_another_window)
	{
		ImGui::Begin("Another Window", &show_another_window);
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
			show_another_window = false;
		ImGui::End();
	}*/

	// 3. Show the ImGui demo window. Most of the sample code is in ImGui::ShowDemoWindow(). Read its code to learn more about Dear ImGui!
	if (m_bshow_demo_window)
	{
		ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver); // Normally user code doesn't need/want to call this because positions are saved in .ini file anyway. Here we just want to make the demo initial state a bit more friendly!
		ImGui::ShowDemoWindow(&m_bshow_demo_window);
	}
}
#endif//defined(DEBUG)
