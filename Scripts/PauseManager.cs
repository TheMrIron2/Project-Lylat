using Godot;

public class PauseManager : Node
{
	private Label ammoLabel;
	private PopupDialog pauseScreen;
	private Button resumeButton;
	private Button settingsButton;
	private Button quitButton;
	private ConfirmationDialog dialog;
	private SettingsManager settings;
	private AudioStreamPlayer audio;

	public override void _Ready()
	{
		ammoLabel = GetNode<Label>("./UI/LabelAmmoSpeed");
		pauseScreen = GetNode<PopupDialog>("./UI/Popup");
		resumeButton = GetNode<Button>("./UI/Popup/Resume");
		settingsButton = GetNode<Button>("./UI/Popup/Settings");
		quitButton = GetNode<Button>("./UI/Popup/Quit");
		dialog = GetNode<ConfirmationDialog>("./UI/Popup/Confirmation");
		settings = GetNode<SettingsManager>("./UI/Settings");
		audio = GetNode<AudioStreamPlayer>("./Audio");

		dialog.Connect("confirmed", this, nameof(Confirmation));
	}

	public override void _Input(InputEvent @event)
	{
		if (@event is InputEventKey eventKey && eventKey.Pressed && eventKey.Scancode == (int)KeyList.Escape)
		{
			if (settings.Visible)
			{
				settings.Visible = false;
				return;
			}

			ammoLabel.Visible = !ammoLabel.Visible;
			pauseScreen.Visible = !pauseScreen.Visible;
			audio.StreamPaused = !audio.StreamPaused;
			
			if (pauseScreen.Visible) Input.SetMouseMode(Input.MouseMode.Visible);
			else Input.SetMouseMode(Input.MouseMode.Captured);
			
			GetTree().Paused = !GetTree().Paused;
		}
	}

	public override void _Process(float delta)
	{
		if (resumeButton.Pressed)
		{
			GetTree().Paused = false;
			ammoLabel.Visible = true;
			pauseScreen.Visible = false;
			if (dialog.Visible) dialog.Visible = false;
			Input.SetMouseMode(Input.MouseMode.Captured);
		}

		if (quitButton.Pressed) dialog.Popup_();
		if (settingsButton.Pressed) settings.Visible = true;
		if (!audio.Playing && !audio.StreamPaused) audio.Play();
	}

	public void Confirmation()
	{
		audio.Stop();
		GetTree().Paused = false;
		GetTree().ChangeScene("res://Scenes/Menu.tscn");
	}
}
