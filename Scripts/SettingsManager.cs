using Godot;
using Newtonsoft.Json;
using System.IO;

public class SettingsJSON
{
	[JsonProperty("msaa_level")]
	public int MSAA { get; set; }

	[JsonProperty("vsync")]
	public bool VSync { get; set; }

	[JsonProperty("resHori")]
	public float ResolutionHorizontal { get; set; }

	[JsonProperty("resVert")]
	public float ResolutionVertical { get; set; }

	[JsonProperty("wmode")]
	public int WindowMode { get; set; }

	public static SettingsJSON Load() => JsonConvert.DeserializeObject<SettingsJSON>(System.IO.File.ReadAllText("settings.json"));

	public void Save()
	{
		StreamWriter writer = new StreamWriter("settings.json");
		writer.Write(JsonConvert.SerializeObject(this));
		writer.Close();
	}
}

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

	private bool visible = false;

	private void setupSelections()
	{
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

		if (OS.WindowFullscreen) windowType.Selected = 0;
		else if (OS.WindowBorderless) windowType.Selected = 1;
		else windowType.Selected = 2;

		if (OS.VsyncEnabled) vsyncButton.Pressed = true;

		resLevelHorizontal.Text = OS.WindowSize.x.ToString();
		resLevelVertical.Text = OS.WindowSize.y.ToString();
	}

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

		windowType.AddItem("Fullscreen");
		windowType.AddItem("Borderless");
		windowType.AddItem("Windowed");

		setupSelections();
	}

	public override void _Process(float delta)
	{
		if (!Visible) return;

		if (!visible)
		{
			setupSelections();
			visible = true;
		}

		if (back.Pressed)
		{
			Visible = false;
			visible = false;
		}

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

		switch (msaaSlider.Value)
		{
		case 0:
			msaaLevel.Text = "0x";
			break;

		case 1:
			msaaLevel.Text = "2x";
			break;

		case 2:
			msaaLevel.Text = "4x";
			break;

		case 3:
			msaaLevel.Text = "8x";
			break;

		case 4:
			msaaLevel.Text = "16x";
			break;
		}

		if (windowType.Selected >= 3) windowType.Selected = 0;
		else if (windowType.Selected <= -1) windowType.Selected = 2;

		if (apply.Pressed)
		{
			int msaa = 0;

			switch (msaaSlider.Value)
			{
			case 0:
				GetViewport().Msaa = Viewport.MSAA.Disabled;
				break;

			case 1:
				GetViewport().Msaa = Viewport.MSAA.Msaa2x;
				msaa = 1;
				break;

			case 2:
				GetViewport().Msaa = Viewport.MSAA.Msaa4x;
				msaa = 2;
				break;

			case 3:
				GetViewport().Msaa = Viewport.MSAA.Msaa8x;
				msaa = 3;
				break;

			case 4:
				GetViewport().Msaa = Viewport.MSAA.Msaa16x;
				msaa = 4;
				break;
			}

			if (vsyncButton.Pressed) OS.VsyncEnabled = true;
			else OS.VsyncEnabled = false;

			float hori = float.Parse(resLevelHorizontal.Text);
			float vert = float.Parse(resLevelVertical.Text);

			OS.WindowSize = new Vector2(hori, vert);
			OS.WindowPosition = new Vector2(OS.GetScreenSize().x - hori, OS.GetScreenSize().y - vert);

			switch (windowType.Selected)
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

			new SettingsJSON
			{
				MSAA = msaa,
				VSync = vsyncButton.Pressed,
				ResolutionHorizontal = float.Parse(resLevelHorizontal.Text),
				ResolutionVertical = float.Parse(resLevelVertical.Text),
				WindowMode = windowType.Selected
			}.Save();
		}
	}
}
