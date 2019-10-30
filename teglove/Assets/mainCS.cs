//# define use_kalman
//# define move_hand

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO.Ports;
using Kalman;

public class mainCS : MonoBehaviour
{
    GameObject Lhand, Lhand1;
    GameObject Lthumb1, Lthumb2, Lthumb3;
    GameObject Lindex1, Lindex2, Lindex3;
    GameObject Lmiddle1, Lmiddle2, Lmiddle3;
    GameObject Lring1, Lring2, Lring3;
    GameObject Lpinky0, Lpinky1, Lpinky2, Lpinky3;
    
    SerialPort sp = new SerialPort("COM1", 9600, Parity.None, 8, StopBits.One);
    public float speed = 1f;
    public float moveSpeed = 0.02f;
    public float rotSpeed = 10f;

#if (use_kalman)
    IKalmanWrapper kalman0, kalman1, kalman2, kalman3;
#endif

    // Use this for initialization
    void Start ()
    {
        sp.Open();
        sp.ReadTimeout = 50;

#if (use_kalman)
        // Using Kalman filter
        kalman0 = new MatrixKalmanWrapper();
        kalman1 = new MatrixKalmanWrapper();
        kalman2 = new MatrixKalmanWrapper();
        kalman3 = new MatrixKalmanWrapper();
#endif

#if (move_hand)
        Lhand = GameObject.Find("l_hand_skeletal");
#endif

        Lhand1 = GameObject.Find("l_hand_skeletal/hands:l_hand_world/hands:b_l_hand");

        Lthumb1 = GameObject.Find("l_hand_skeletal/hands:l_hand_world/hands:b_l_hand/hands:b_l_thumb1");
        Lthumb2 = GameObject.Find("l_hand_skeletal/hands:l_hand_world/hands:b_l_hand/hands:b_l_thumb1/hands:b_l_thumb2");
        Lthumb3 = GameObject.Find("l_hand_skeletal/hands:l_hand_world/hands:b_l_hand/hands:b_l_thumb1/hands:b_l_thumb2/hands:b_l_thumb3");

        Lindex1 = GameObject.Find("l_hand_skeletal/hands:l_hand_world/hands:b_l_hand/hands:b_l_index1");
        Lindex2 = GameObject.Find("l_hand_skeletal/hands:l_hand_world/hands:b_l_hand/hands:b_l_index1/hands:b_l_index2");
        Lindex3 = GameObject.Find("l_hand_skeletal/hands:l_hand_world/hands:b_l_hand/hands:b_l_index1/hands:b_l_index2/hands:b_l_index3");

        Lmiddle1 = GameObject.Find("l_hand_skeletal/hands:l_hand_world/hands:b_l_hand/hands:b_l_middle1");
        Lmiddle2 = GameObject.Find("l_hand_skeletal/hands:l_hand_world/hands:b_l_hand/hands:b_l_middle1/hands:b_l_middle2");
        Lmiddle3 = GameObject.Find("l_hand_skeletal/hands:l_hand_world/hands:b_l_hand/hands:b_l_middle1/hands:b_l_middle2/hands:b_l_middle3");

        Lring1 = GameObject.Find("l_hand_skeletal/hands:l_hand_world/hands:b_l_hand/hands:b_l_ring1");
        Lring2 = GameObject.Find("l_hand_skeletal/hands:l_hand_world/hands:b_l_hand/hands:b_l_ring1/hands:b_l_ring2");
        Lring3 = GameObject.Find("l_hand_skeletal/hands:l_hand_world/hands:b_l_hand/hands:b_l_ring1/hands:b_l_ring2/hands:b_l_ring3");

        Lpinky0 = GameObject.Find("l_hand_skeletal/hands:l_hand_world/hands:b_l_hand/hands:b_l_pinky0");
        Lpinky1 = GameObject.Find("l_hand_skeletal/hands:l_hand_world/hands:b_l_hand/hands:b_l_pinky0/hands:b_l_pinky1");
        Lpinky2 = GameObject.Find("l_hand_skeletal/hands:l_hand_world/hands:b_l_hand/hands:b_l_pinky0/hands:b_l_pinky1/hands:b_l_pinky2");
        Lpinky3 = GameObject.Find("l_hand_skeletal/hands:l_hand_world/hands:b_l_hand/hands:b_l_pinky0/hands:b_l_pinky1/hands:b_l_pinky2/hands:b_l_pinky3");
    }

    // Update is called once per frame
    void Update ()
    {
        //if (Input.GetKey(KeyCode.M))
        //{
        //    //print("You pressed the A key");
        //    //transform.Rotate(0f, 0f, 10f * Time.deltaTime);
        //    //Lhand1.transform.localRotation = Quaternion.RotateTowards(
        //    //Lhand1.transform.localRotation,
        //    //Quaternion.Euler(10f,
        //    //                 0f,
        //    //                 0f),
        //    //60f);

        //    //transform.RotateAround(Lhand1.transform.forward, 10f);
        //    Lhand1.transform.Rotate(
        //        Input.GetAxis("AroundX") * rotSpeed,
        //        Input.GetAxis("AroundY") * rotSpeed,
        //        Input.GetAxis("AroundZ") * rotSpeed, 
        //        Space.Self);
        //    print(Input.GetAxis("AroundX") * rotSpeed);

        //}

        transform.Translate(Input.GetAxis("Horizontal") * moveSpeed * Time.deltaTime, 
                            Input.GetAxis("Vertical") * moveSpeed * Time.deltaTime,
                            Input.GetAxis("Depth") * moveSpeed * Time.deltaTime);

        Lhand1.transform.Rotate(
                Input.GetAxis("AroundX") * rotSpeed,
                Input.GetAxis("AroundY") * rotSpeed,
                Input.GetAxis("AroundZ") * rotSpeed,
                Space.Self);

        Lthumb2.transform.Rotate(
                0f,
                0f,
                Input.GetAxis("Lthumb2") * rotSpeed,
                Space.Self);
        //print(Input.GetAxis("Lthumb2") * rotSpeed);

        Lindex2.transform.Rotate( 
                0f,
                0f,
                Input.GetAxis("Lindex2") * rotSpeed,
                Space.Self);

        Lmiddle2.transform.Rotate(
                0f,
                0f,
                Input.GetAxis("Lmiddle2") * rotSpeed,
                Space.Self);

        Lring2.transform.Rotate(
                0f,
                0f,
                Input.GetAxis("Lring2") * rotSpeed,
                Space.Self);

        Lpinky2.transform.Rotate(
                0f,  
                0f,
                Input.GetAxis("Lpinky2") * rotSpeed,
                Space.Self);

        if (sp.IsOpen)
        {
            try
            {
                string a = sp.ReadLine();
                string[] pos = a.Split(new char[] { ' ' });

                int rot0, rot1, rot2, rot3;
                int.TryParse(pos[0], out rot0);
                int.TryParse(pos[1], out rot1);
                int.TryParse(pos[2], out rot2);
                int.TryParse(pos[3], out rot3);

#if (use_kalman)
                // Using Kalman filter
                Vector3 rot0a = new Vector3(0, 0, rot0);
                Vector3 rot1a = new Vector3(0, 0, rot1);
                Vector3 rot2a = new Vector3(0, 0, rot2);
                Vector3 rot3a = new Vector3(0, 0, rot3);

                Vector3 rot0b, rot1b, rot2b, rot3b;

                rot0b = kalman0.Update(rot0a);
                rot1b = kalman1.Update(rot1a);
                rot2b = kalman2.Update(rot2a);
                rot3b = kalman3.Update(rot3a);

                MoveObject((int)rot0b.z, (int)rot1b.z, (int)rot2b.z, (int)rot3b.z);
#else
                // Raw data
                MoveObject(rot0, rot1, rot2, rot3);
#endif

#if (move_hand)
                Vector3 mouse = Input.mousePosition;
                mouse.z = 10;
                Lhand.transform.position = mouse/1000;
#endif
            }
            catch (System.Exception)
            {
            }
        }
    }

    void MoveObject(int obj0, int obj1, int obj2, int obj3)
    {
        Lthumb1.transform.localRotation = Quaternion.RotateTowards(Lthumb1.transform.localRotation, Quaternion.Euler(0, 160, 40 - 0.5f * obj0), 20f);
        Lthumb2.transform.localRotation = Quaternion.RotateTowards(Lthumb2.transform.localRotation, Quaternion.Euler(0, 0, 0 - 0.35f * obj0), 20f);
        Lthumb3.transform.localRotation = Quaternion.RotateTowards(Lthumb3.transform.localRotation, Quaternion.Euler(0, 0, 15 - 0.35f * obj0), 20f);

        Lindex1.transform.localRotation = Quaternion.RotateTowards(Lindex1.transform.localRotation, Quaternion.Euler(287f, 101f, 84 - obj1), 20f);
        Lindex2.transform.localRotation = Quaternion.RotateTowards(Lindex2.transform.localRotation, Quaternion.Euler(0, 0, 0 - 0.5f * obj1), 20f);
        Lindex3.transform.localRotation = Quaternion.RotateTowards(Lindex3.transform.localRotation, Quaternion.Euler(0, 0, 0 - 0.5f * obj1), 20f);

        Lmiddle1.transform.localRotation = Quaternion.RotateTowards(Lmiddle1.transform.localRotation, Quaternion.Euler(-80.4f, 18.7f, 165 - 0.7f * obj2), 20f);
        Lmiddle2.transform.localRotation = Quaternion.RotateTowards(Lmiddle2.transform.localRotation, Quaternion.Euler(0, 0, 0 - 0.6f * obj2), 20f);
        Lmiddle3.transform.localRotation = Quaternion.RotateTowards(Lmiddle3.transform.localRotation, Quaternion.Euler(0, 0, 0 - 0.6f * obj2), 20f);

        Lring1.transform.localRotation = Quaternion.RotateTowards(Lring1.transform.localRotation, Quaternion.Euler(-70f, -21.5f, -163 - 0.7f * obj3), 20f);
        Lring2.transform.localRotation = Quaternion.RotateTowards(Lring2.transform.localRotation, Quaternion.Euler(0, 0, 0 - 0.6f * obj3), 20f);
        Lring3.transform.localRotation = Quaternion.RotateTowards(Lring3.transform.localRotation, Quaternion.Euler(0, 0, 0 - 0.6f * obj3), 20f);
    }
}
