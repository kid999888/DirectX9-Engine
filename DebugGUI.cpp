//=================================================================================================
//                                                        
//　　　DebugGUIクラスプログラム[Renderer.h]
//      Author:王暁晨(AT-13A-281 04)　2018.06.13      
//                                                        
//=================================================================================================

//=================================================================================================
//　　　ヘッダファイル           
//=================================================================================================
#include"DebugGUI.h"

//=================================================================================================
//　　　インスタンス実体化          
//=================================================================================================
bool CDebugGUI::m_bshow_demo_window = false;
ImVec4 CDebugGUI::m_v4clear_color = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);

//=================================================================================================
//　　　DebugGUIクラス初期処理         
//=================================================================================================

bool CDebugGUI::Init(void)
{
	//ImGUI処理
	m_bshow_demo_window = false;
	m_v4clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	return true;
}

void CDebugGUI::UpdateWindow(void)
{
	ImGui_ImplDX9_NewFrame();
	/*ImGui::Text("123");*/

	// 1. Show a simple window.
	// Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets automatically appears in a window called "Debug".
	{
		static float f = 0.0f;
		static int counter = 0;
		ImGui::Text("Hello, world!");                           // Display some text (you can use a format string too)
		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
		ImGui::ColorEdit3("clear color", (float*)&m_v4clear_color); // Edit 3 floats representing a color

		ImGui::Checkbox("Demo Window", &m_bshow_demo_window);      // Edit bools storing our windows open/close state
		/*ImGui::Checkbox("Another Window", &show_another_window);*/

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
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
