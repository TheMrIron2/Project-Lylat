using Godot;

public class ArwingBody : KinematicBody
{
    public override void _PhysicsProcess(float delta)
    {
        KinematicCollision collision = MoveAndCollide(GetFloorVelocity() * delta);
        if (collision != null) GetFloorVelocity().Slide(collision.Normal);

        GetNode<Spatial>("./..").GlobalTransform = GlobalTransform;
    }
}
