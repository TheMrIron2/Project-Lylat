using Godot;

public class SettingsManager : Control
{
	private Button apply;
	private Button back;
	private Slider msaaSlider;
	private Label msaaLevel;
	private CheckButton vsyncButton;
	private LineEdit resLevelHorizontal;
	private LineEdit resLevelVertical;
	private OptionButton windowType;

	public override void _Ready()
	{
		apply = GetNode<Button>("./Apply");
		back = GetNode<Button>("./Back");
		msaaSlider = GetNode<Slider>("./MSAA/Slider");
		msaaLevel = GetNode<Label>("./MSAA/Level");
		vsyncButton = GetNode<CheckButton>("./VSync");
		resLevelHorizontal = GetNode<LineEdit>("./Resolution/Horizontal");
		resLevelVertical = GetNode<LineEdit>("./Resolution/Vertical");
		windowType = GetNode<OptionButton>("./Window");

		switch (GetViewport().Msaa)
		{
		case Viewport.MSAA.Msaa2x:
			msaaSlider.Value = 1;
			msaaLevel.Text = "2x";
			break;

		case Viewport.MSAA.Msaa4x:
			msaaSlider.Value = 2;
			msaaLevel.Text = "4x";
			break;

		case Viewport.MSAA.Msaa8x:
			msaaSlider.Value = 3;
			msaaLevel.Text = "8x";
			break;

		case Viewport.MSAA.Msaa16x:
			msaaSlider.Value = 4;
			msaaLevel.Text = "16x";
			break;
		}

		if (OS.VsyncEnabled) vsyncButton.Pressed = true;

		resLevelHorizontal.Text = OS.WindowSize.x.ToString();
		resLevelVertical.Text = OS.WindowSize.y.ToString();

		windowType.AddItem("Fullscreen");
		windowType.AddItem("Borderless");
		windowType.AddItem("Windowed");

		if (OS.WindowFullscreen) windowType.Selected = 0;
		else if (OS.WindowBorderless) windowType.Selected = 1;
		else windowType.Selected = 2;
	}

	public override void _Process(float delta)
	{
		if (back.Pressed) GetTree().ChangeScene("res://Scenes/Menu.tscn");

		switch (msaaSlider.Value)
		{
		case 0:
			GetViewport().Msaa = Viewport.MSAA.Disabled;
			msaaLevel.Text = "0x";
			break;

		case 1:
			GetViewport().Msaa = Viewport.MSAA.Msaa2x;
			msaaLevel.Text = "2x";
			break;

		case 2:
			GetViewport().Msaa = Viewport.MSAA.Msaa4x;
			msaaLevel.Text = "4x";
			break;

		case 3:
			GetViewport().Msaa = Viewport.MSAA.Msaa8x;
			msaaLevel.Text = "8x";
			break;

		case 4:
			GetViewport().Msaa = Viewport.MSAA.Msaa16x;
			msaaLevel.Text = "16x";
			break;
		}
		
		if (vsyncButton.Pressed) OS.VsyncEnabled = true;
		else OS.VsyncEnabled = false;

		switch (windowType.Selected)
		{
		case 0:
			windowType.Text = "Fullscreen";
			break;
			
		case 1:
			windowType.Text = "Borderless";
			break;

		case 2:
			windowType.Text = "Windowed";
			break;
		}

		if (windowType.Selected >= 3) windowType.Selected = 0;
		else if (windowType.Selected <= -1) windowType.Selected = 2;

		if (apply.Pressed)
		{
			OS.WindowSize = new Vector2(float.Parse(resLevelHorizontal.Text), float.Parse(resLevelVertical.Text));
			OS.WindowPosition = new Vector2(0, 0);

			switch (windowType.Selected)
			{
			case 0:
				OS.WindowBorderless = false;
				OS.WindowFullscreen = true;
				OS.WindowResizable = false;
				break;
			
			case 1:
				OS.WindowBorderless = true;
				OS.WindowFullscreen = false;
				OS.WindowResizable = false;
				break;

			case 2:
				OS.WindowBorderless = false;
				OS.WindowFullscreen = false;
				OS.WindowResizable = true;
				break;
			}
		}
	}
}
