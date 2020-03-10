using Godot;
using System;
using System.Threading;

public class ThreadedLoader
{
    public PackedScene Content { get; private set; }
    public bool Done { get; private set; }
    public Exception Exception { get; private set; }

    private string filepath;
    private System.Threading.Thread thread;
    
    public ThreadedLoader(string path)
    {
        Content = null;
        Done = false;
        Exception = null;

        filepath = path;
        thread = new System.Threading.Thread(new ThreadStart(loaderThread));
    }

    public void Start() => thread.Start();

    private void loaderThread()
    {
        ResourceInteractiveLoader loader = ResourceLoader.LoadInteractive(filepath);

        while (!Done)
        {
            Error error = loader.Poll();
            switch (error)
            {
            case Error.Ok:
                break;

            case Error.FileEof:
                Content = (PackedScene)loader.GetResource();
                Done = true;
                break;
            
            default:
                Exception = new Exception(error.ToString());
                return;
            }
            
        }
    }
}