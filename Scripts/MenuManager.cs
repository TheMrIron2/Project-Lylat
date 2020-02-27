using Godot;

public class MenuManager : Node
{
	private Button start;
	private Button settings;
	private Button quit;
	private SettingsManager dialog;

	/*public override void _Ready()
	{
		applySettings(new SettingsJSON());

		start = GetNode<Button>("./UIView/Container/Start");
		settings = GetNode<Button>("./UIView/Container/Settings");
		quit = GetNode<Button>("./UIView/Container/Quit");
		dialog = GetNode<SettingsManager>("./UI/Dialog");
	}

	public override void _Process(float delta)
	{
		if (start.Pressed) GetTree().ChangeScene("res://Scenes/Game.tscn");
		else if (settings.Pressed) dialog.Visible = true;
		else if (quit.Pressed) GetTree().Quit();
	}*/

	private void applySettings(SettingsJSON json)
	{
		ResourceLoader.Load<PackedScene>("").Instance
		switch (json.MSAA)
		{
		case 0:
			GetViewport().Msaa = Viewport.MSAA.Disabled;
			break;

		case 1:
			GetViewport().Msaa = Viewport.MSAA.Msaa2x;
			break;

		case 2:
			GetViewport().Msaa = Viewport.MSAA.Msaa4x;
			break;

		case 3:
			GetViewport().Msaa = Viewport.MSAA.Msaa8x;
			break;

		case 4:
			GetViewport().Msaa = Viewport.MSAA.Msaa16x;
			break;
		}

		if (json.VSync) OS.VsyncEnabled = true;
		else OS.VsyncEnabled = false;

		OS.WindowSize = new Vector2(json.ResolutionHorizontal, json.ResolutionVertical);
		OS.WindowPosition = new Vector2(OS.GetScreenSize().x - json.ResolutionHorizontal, OS.GetScreenSize().y - json.ResolutionVertical);
		
		switch (json.WindowMode)
		{
		case 0:
			OS.WindowBorderless = false;
			OS.WindowFullscreen = true;
			break;
		
		case 1:
			OS.WindowBorderless = true;
			OS.WindowFullscreen = false;
			break;

		case 2:
			OS.WindowBorderless = false;
			OS.WindowFullscreen = false;
			break;
		}
	}
}
