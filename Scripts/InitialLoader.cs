using Godot;
using System;

public class InitialLoader : Control
{
	private ThreadedLoader loader;

	private Label info;
	private TextureRect loading;
	
	private float alphaCounter;
	private float timeCounter;
	private bool alphaDecrease;
	private bool textDone;
	private bool waitText;
	
	
	public override void _Ready()
	{
		Input.SetMouseMode(Input.MouseMode.Hidden);

		loading = GetNode<TextureRect>("./Loading");
		info = GetNode<Label>("./Info");

		loader = new ThreadedLoader("res://Scenes/Menu.tscn");

		alphaCounter = 0.0f;
		timeCounter = 0.0f;
		alphaDecrease = false;
		textDone = false;
		waitText = true;

		loader.Start();
	}

	public override void _Process(float delta)
	{
		if (loader.Exception != null) throw new Exception($"Loading the Menu failed: \"{loader.Exception.Message}\"");

		if (loader.Done && textDone)
		{
			System.Threading.Thread.Sleep(300);
			GetTree().ChangeSceneTo(loader.Content);
		}

		if (loading.RectRotation == 360.0f) loading.RectRotation = 0.0f;
		loading.RectRotation = loading.RectRotation + 0.1f;

		if (alphaDecrease && waitText)
		{
			if (timeCounter >= 150.0f) waitText = false;
			timeCounter = timeCounter + 0.01f;
			return;
		}

		info.SelfModulate = new Color(info.SelfModulate.r, info.SelfModulate.g, info.SelfModulate.b, alphaCounter);
		if (alphaDecrease && loading.SelfModulate.a > alphaCounter) loading.SelfModulate = new Color(loading.SelfModulate.r, loading.SelfModulate.g, loading.SelfModulate.b, alphaCounter);
		if (!alphaDecrease) alphaCounter = alphaCounter + 0.001f;
		else alphaCounter = alphaCounter - 0.001f;

		if (alphaCounter >= 1.0f) alphaDecrease = true;
		else if (alphaCounter <= 0.0f && alphaDecrease) textDone = true;
	}


}
