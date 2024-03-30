using UnityEngine;
using System.Collections;
using InControl;

public class PlayerMovement : MonoBehaviour
{
    // Player info
    private PlayerActions m_PlayerActions;
    private Rigidbody2D m_PlayerRigidBody;
    private Animator m_PlayerAnimator;

    // Use this for initialization
    void Start ()
    {
        // Get components
		m_PlayerRigidBody = GetComponent<Rigidbody2D> ();
		m_PlayerAnimator = GetComponent<Animator> ();

        // Bind available actions
        m_PlayerActions = new PlayerActions();
        m_PlayerActions.Left.AddDefaultBinding(Key.LeftArrow);
        m_PlayerActions.Left.AddDefaultBinding(InputControlType.DPadLeft);
        m_PlayerActions.Right.AddDefaultBinding(Key.RightArrow);
        m_PlayerActions.Right.AddDefaultBinding(InputControlType.DPadRight);
        m_PlayerActions.Up.AddDefaultBinding(Key.UpArrow);
        m_PlayerActions.Up.AddDefaultBinding(InputControlType.DPadUp);
        m_PlayerActions.Down.AddDefaultBinding(Key.DownArrow);
        m_PlayerActions.Down.AddDefaultBinding(InputControlType.DPadDown);
    }
	
	// Update is called once per frame
	void Update ()
    {
		// Gets a movement vector of absolute integer values (-1 to 0 to 1)
		// Button pressed/button not pressed
		Vector2 vMovement = new Vector2 (GetHorizontalMovement(), GetVerticalMovement());
		if (vMovement != Vector2.zero)
        {
			m_PlayerAnimator.SetBool ("iswalking", true);
            m_PlayerAnimator.SetFloat ("input_x", vMovement.x);
            m_PlayerAnimator.SetFloat ("input_y", vMovement.y);
		}
        else
        {
            m_PlayerAnimator.SetBool ("iswalking", false);
		}

        // Use the non-force related method since we want a safe translate
        m_PlayerRigidBody.MovePosition (m_PlayerRigidBody.position + vMovement * Time.deltaTime);
	}

    float GetHorizontalMovement()
    {
        return m_PlayerActions.MoveHorz.Value;
    }

    float GetVerticalMovement()
    {
        return m_PlayerActions.MoveVert.Value;
    }
}
