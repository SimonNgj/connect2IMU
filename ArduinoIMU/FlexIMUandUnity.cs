using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Kalman;

public class main : MonoBehaviour
{
    // Start is called before the first frame update
    [SerializeField]
    Camera cam;

    [SerializeField]
    Transform filterdHand;

    IKalmanWrapper kalman;
    GameObject Lhand;
    int i = 0;

    void Start()
    {
        kalman = new MatrixKalmanWrapper();

        // Left hand
        Lhand = GameObject.Find("l_hand_skeletal/hands:l_hand_world/hands:b_l_hand");
    }

    // Update is called once per frame
    void Update()
    {
        Vector3 mouse = Input.mousePosition;
        mouse.z = 30;

        filterdHand.transform.position = cam.ScreenToWorldPoint(kalman.Update(mouse))/50;

        i++;
        Lhand.transform.localRotation = Quaternion.RotateTowards(Lhand.transform.localRotation, Quaternion.Euler(-45, 90, 180-i/10), 20f);
    }
}
