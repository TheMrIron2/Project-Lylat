using Godot;

public class MenuController : Node
{
	private AnimationPlayer animation;
	private AudioStreamPlayer music;
	private AudioStreamPlayer effects;

	private Arwing arwing;
	
	private Control mainUI;
	private Button mainStart;
	private Button mainSettings;
	private Button mainQuit;
	private TextureRect mainQuitMessageBox;
	private Label mainQuitMessage;
	private Button mainQuitAccept;
	private Button mainQuitDecline;

	private Control settingsUI;
	private Label settingsVersion;
	private Button settingsBack;

	private bool switchToSettings;

	public override void _Ready()
	{
		Input.SetMouseMode(Input.MouseMode.Visible);

		animation           = GetNode<AnimationPlayer>("./Animation");
		music               = GetNode<AudioStreamPlayer>("./Music");
		effects             = GetNode<AudioStreamPlayer>("./Effects");

		arwing              = GetNode<Arwing>("./Spatial/Arwing");

		mainUI              = GetNode<Control>("./MainUI");
		mainStart           = GetNode<Button>("./MainUI/Start");
		mainSettings        = GetNode<Button>("./MainUI/Settings");
		mainQuit            = GetNode<Button>("./MainUI/Quit");

		mainQuitMessageBox	= GetNode<TextureRect>("./MainUI/QuitMessage");
		mainQuitMessage		= GetNode<Label>("./MainUI/QuitMessage/Message");
		mainQuitAccept		= GetNode<Button>("./MainUI/QuitMessage/Accept");
		mainQuitDecline		= GetNode<Button>("./MainUI/QuitMessage/Decline");

		settingsUI          = GetNode<Control>("./SettingsUI");
		settingsBack        = GetNode<Button>("./SettingsUI/Back");
		settingsVersion     = GetNode<Label>("./SettingsUI/Version");

		switchToSettings    = false;

		settingsVersion.Text = $"Version {typeof(MenuController).Assembly.GetName().Version}";

		string osName;

		switch (OS.GetName())
		{
		case "OSX":
			osName = "macOS";
			break;

		case "X11":
			osName = "Linux";
			break;

		default:
			osName = OS.GetName();
			break;
		}

		mainQuitMessage.Text = $"Do you want to go back to {osName}?";

		arwing.MenuMode(true);
		animation.Play("CameraIntroduction");
	}

	public override void _Process(float delta)
	{
		if (!animation.IsPlaying())
		{
			// TODO: fadein UI
			if (!switchToSettings) mainUI.Show();
			else settingsUI.Show();
		}

		if (mainQuitMessageBox.Visible)
		{
			if (mainQuitAccept.Pressed) GetTree().Quit();
			else if (mainQuitDecline.Pressed) mainQuitMessageBox.Visible = false;
		}

		// TODO: Loading manager
		// TODO: Settings logic
		
		if (mainStart.Pressed) GetTree().ChangeScene("res://Scenes/Maps/1.tscn");
		if (mainSettings.Pressed)
		{
			// TODO: UI viewport
			mainUI.Visible = false;
			switchToSettings = true;
			animation.Play("CameraMoveToSettings");
		}

		if (mainQuit.Pressed) mainQuitMessageBox.Visible = true;

		if (settingsBack.Pressed)
		{
			settingsUI.Visible = false;
			switchToSettings = false;
			animation.PlayBackwards("CameraMoveToSettings");
		}
	}
}
