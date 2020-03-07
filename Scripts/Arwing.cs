using Godot;

public class Arwing : Spatial
{
    public enum ControlMode
    {
        FixedMovement,
        FullMovement
    }

    public enum VelocityMode
    {
        Constant,
        Controllable
    }

    private AnimationPlayer animation;
    private StaticBody body;
    private AudioStreamPlayer3D effects;

    public override void _Ready()
    {
        animation   = GetNode<AnimationPlayer>("./Animation");
        body        = GetNode<StaticBody>("./Body");
        effects     = GetNode<AudioStreamPlayer3D>("./Effects");
    }

    public override void _Process(float delta)
    {
        if (!animation.IsPlaying() && animation.GetAnimationList().Length != 0) foreach (string name in animation.GetAnimationList()) animation.RemoveAnimation(name);
    }

    public void UTurn()
    {
        Animation anim = new Animation();
        Vector3 pos = new Vector3(GlobalTransform.origin.Normalized());
        Vector3 scale = new Vector3(1, 1, 1);

        anim.AddTrack(Animation.TrackType.Transform, 0);
        anim.TrackSetPath(0, "Body");

        anim.Length = 2.4f;

        anim.TransformTrackInsertKey(0, 0, new Vector3(pos.x, pos.y, pos.z), new Quat(Rotation.x, Rotation.y, Rotation.z, 1).Normalized(), scale);
        anim.TransformTrackInsertKey(0, 0.6f, new Vector3(pos.x, pos.y, pos.z + 45), new Quat(Rotation.x, Rotation.y, Rotation.z, 1).Normalized(), scale);
        anim.TransformTrackInsertKey(0, 0.8f, new Vector3(pos.x, pos.y + 10, pos.z + 55), new Quat(Rotation.x - 0.2f, Rotation.y, Rotation.z, 0.9f).Normalized(), scale);
        anim.TransformTrackInsertKey(0, 1, new Vector3(pos.x, pos.y + 20, pos.z + 65), new Quat(Rotation.x - 0.4f, Rotation.y, Rotation.z, 0.8f).Normalized(), scale);
        anim.TransformTrackInsertKey(0, 1.2f, new Vector3(pos.x , pos.y + 30, pos.z + 65), new Quat(Rotation.x - 0.7f, Rotation.y, Rotation.z, 0.7f).Normalized(), scale);
        anim.TransformTrackInsertKey(0, 1.4f, new Vector3(pos.x, pos.y + 45, pos.z + 55), new Quat(Rotation.x - 0.8f, Rotation.y, Rotation.z, 0.5f).Normalized(), scale);
        anim.TransformTrackInsertKey(0, 1.6f, new Vector3(pos.x, pos.y + 50, pos.z + 45), new Quat(Rotation.x + 0.9f, Rotation.y, Rotation.z, -0.3f).Normalized(), scale);
        anim.TransformTrackInsertKey(0, 1.8f, new Vector3(pos.x, pos.y + 55, pos.z + 35), new Quat(Rotation.x + 1, Rotation.y, Rotation.z, 0).Normalized(), scale);
        anim.TransformTrackInsertKey(0, 2.4f, new Vector3(pos.x, pos.y, pos.z), new Quat(Rotation.x, Rotation.y, Rotation.z, 0).Normalized(), scale);

        animation.AddAnimation("uturn", anim);
        animation.Play("uturn");
    }
}
