package com.example.wiidroid;

import android.app.Activity;
import android.content.Intent;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnTouchListener;
import android.widget.Button;
import android.widget.TextView;

public class SteeringWheel extends Activity {
	SensorManager mySensorManager;//SensorManager��������	
	Sensor myAccelerometer; //���ٶȴ�����
	/*TextView tvX;	//TextView��������	
	TextView tvY;	//TextView��������	
	TextView tvZ;	//TextView��������
	TextView info;*/
	TextView direc;
	int state=0;
	String connip;
	Button UpButton,SpaceButton,DownButton,EnterButton;
	//SocketClient client;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_swheel);
		Intent intent = getIntent();
		connip = intent.getStringExtra("socketip");
		//client = new SocketClient(connip,12345);
		
		//tvX = (TextView)findViewById(R.id.tvX);	//������ʾx�᷽����ٶ�
        //tvY = (TextView)findViewById(R.id.tvY);	//������ʾy�᷽����ٶ�	
        //tvZ = (TextView)findViewById(R.id.tvZ); //������ʾz�᷽����ٶ�
        //info= (TextView)findViewById(R.id.info);//������ʾ�ֻ��м��ٶȴ������������Ϣ
		direc=(TextView)findViewById(R.id.fullscreen_content);
        mySensorManager = (SensorManager)getSystemService(SENSOR_SERVICE);//���SensorManager����	
        myAccelerometer=mySensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);        
        /*String str="\n����: "+myAccelerometer.getName()+"\n��� :"+myAccelerometer.getPower()+
        "\n���� :"+myAccelerometer.getType()+"\nVendor: "+myAccelerometer.getVendor()+
        "\n�汾: "+myAccelerometer.getVersion()+"\n����: "+myAccelerometer.getMaximumRange()+
        "\nIP: "+connip;
        info.setText(str);//����Ϣ�ַ���������Ϊinfo��TextView*/
        UpButton = (Button)findViewById(R.id.button2); 
        DownButton = (Button)findViewById(R.id.Button01);
        SpaceButton = (Button)findViewById(R.id.button1);
        EnterButton = (Button)findViewById(R.id.button3);
        UpButton.setOnTouchListener(
        	new OnTouchListener(){
        		public boolean onTouch(View view, MotionEvent event) {
        			switch(event.getAction()){
        				case MotionEvent.ACTION_DOWN:
        					connsendmsg("1 0 038",connip);
        					break;
        				case MotionEvent.ACTION_UP:
        					connsendmsg("1 1 038",connip);
        					break;
        			}
        			return false;
        		}
        	}
        );
        DownButton.setOnTouchListener(
            new OnTouchListener(){
            	public boolean onTouch(View view, MotionEvent event) {
            		switch(event.getAction()){
            			case MotionEvent.ACTION_DOWN:
            				connsendmsg("1 0 040",connip);
            				break;
            			case MotionEvent.ACTION_UP:
            				connsendmsg("1 1 040",connip);
            				break;
            		}
            		return false;
            	}
            }
        );
        SpaceButton.setOnTouchListener(
           	new OnTouchListener(){
           		public boolean onTouch(View view, MotionEvent event) {
           			switch(event.getAction()){
           				case MotionEvent.ACTION_DOWN:
           					connsendmsg("1 0 032",connip);
           					break;
           				case MotionEvent.ACTION_UP:
           					connsendmsg("1 1 032",connip);
           					break;
           			}
           			return false;
           		}
           	}
        );
        EnterButton.setOnTouchListener(
               	new OnTouchListener(){
               		public boolean onTouch(View view, MotionEvent event) {
               			switch(event.getAction()){
               				case MotionEvent.ACTION_DOWN:
               					connsendmsg("1 0 013",connip);
               					break;
               				case MotionEvent.ACTION_UP:
               					connsendmsg("1 1 013",connip);
               					break;
               			}
               			return false;
               		}
               	}
            );
	}
    @Override
	protected void onResume(){ //��дonResume����
		super.onResume();
		mySensorManager.registerListener(mySensorListener, myAccelerometer, SensorManager.SENSOR_DELAY_NORMAL);
	}	
	@Override
	protected void onPause(){//��дonPause����	
		super.onPause();
		mySensorManager.unregisterListener(mySensorListener);//ȡ��ע�������
	}
	private SensorEventListener mySensorListener = 
		new SensorEventListener(){//����ʵ����SensorEventListener�ӿڵĴ�����������
		@Override
		public void onAccuracyChanged(Sensor sensor, int accuracy){}
		@Override
		public void onSensorChanged(SensorEvent event){
			float []values=event.values;//��ȡ�����᷽����ϵļ��ٶ�ֵ
			//tvX.setText("x�᷽���ϵļ��ٶ�Ϊ��"+values[0]);		
			//tvY.setText("y�᷽���ϵļ��ٶ�Ϊ��"+values[1]);		
			//tvZ.setText("z�᷽���ϵļ��ٶ�Ϊ��"+values[2]);	
			if ((values[1] > 2)&&(state == 0)) {
				//client.sendMsg("1 0 39");
				connsendmsg("1 0 039",connip);
				state = 1;
				//tvY.setText("y�᷽���ϵļ��ٶ�Ϊ��"+values[1]+"��ת");	
				direc.setText("��");
			}
			if ((values[1] > 2)&&(state == -1)) {
				connsendmsg("1 1 037",connip);
				connsendmsg("1 0 039",connip);
				state = 1;
				//tvY.setText("y�᷽���ϵļ��ٶ�Ϊ��"+values[1]+"��ת");	
				direc.setText("��");
			}
			if ((values[1] < 2)&&(values[1] > -2)&&(state == 1)) {
				//client.sendMsg("1 1 39");
				connsendmsg("1 1 039",connip);
				state = 0;
				//tvY.setText("y�᷽���ϵļ��ٶ�Ϊ��"+values[1]+"�һ���");	
				direc.setText("��");
			}
			if ((values[1] < -2)&&(state == 0)) {
				//client.sendMsg("1 0 37");
				connsendmsg("1 0 037",connip);
				state = -1;
				//tvY.setText("y�᷽���ϵļ��ٶ�Ϊ��"+values[1]+"��ת");	
				direc.setText("��");
			}
			if ((values[1] < -2)&&(state == 1)) {
				connsendmsg("1 1 039",connip);
				connsendmsg("1 0 037",connip);
				state = -1;
				//tvY.setText("y�᷽���ϵļ��ٶ�Ϊ��"+values[1]+"��ת");	
				direc.setText("��");
			}
			if ((values[1] < 2)&&(values[1] > -2)&&(state == -1)) {
				//client.sendMsg("1 1 37");
				connsendmsg("1 1 037",connip);
				state = 0;
				//tvY.setText("y�᷽���ϵļ��ٶ�Ϊ��"+values[1]+"�����");	
				direc.setText("��");
			}
			/*if (values[1] > 3) {
				//client.sendMsg("1 0 39");
				connsendmsg("1 0 039",connip);
				direc.setText("������ģʽ\n��");
				//state = 1;
				//tvY.setText("y�᷽���ϵļ��ٶ�Ϊ��"+values[1]+"��ת");	
			}
			if (values[1] < -3) {
				//client.sendMsg("1 0 37");
				connsendmsg("1 0 037",connip);
				direc.setText("������ģʽ\n��");
				//state = -1;
				//tvY.setText("y�᷽���ϵļ��ٶ�Ϊ��"+values[1]+"��ת");	
			}*/
		}};
	public void connsendmsg(String msg, String connip)
	{
		new Connect1(msg,connip,12345).start();
	}
}
