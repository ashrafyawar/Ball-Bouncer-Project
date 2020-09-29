package com.app.ballbouncer;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.util.Random;
import java.util.concurrent.TimeUnit;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.Response;

public class HomeFragment extends Fragment {
    private static String ServerIP = "";
    private static String ServerPort = "";

    private TextView titleText;
    private Button button1,button2,button3;
    private ImageView ball;

    private int x,y,radius;

    public static void setServerData(String ip, String port) {
        HomeFragment.ServerIP = ip;
        HomeFragment.ServerPort = port;
    }

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View v = inflater.inflate(R.layout.fragment_home,container,false);

        titleText = v.findViewById(R.id.titleText);
        button1 = v.findViewById(R.id.button1);
        button2 = v.findViewById(R.id.button2);
        button3 = v.findViewById(R.id.button3);

        ball = v.findViewById(R.id.ball);

        button1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (HomeFragment.ServerIP.equals("") || HomeFragment.ServerPort.equals("")) {
                    return;
                }

                Log.d("Bounce", "Sending Bounce Request...");

                OkHttpClient client = new OkHttpClient();
                String url = "http://" + HomeFragment.ServerIP + ":" + HomeFragment.ServerPort + "/bounce";

                Log.d("Bounce", "URL: " + url);

                Request request = new Request.Builder().url(url).build();
                client.newCall(request).enqueue(new Callback() {
                    @Override
                    public void onFailure(Call call, IOException e) {
                        e.printStackTrace();
                    }
                    @Override
                    public void onResponse(Call call, Response response) throws IOException {
                    }
                });
                Log.d("Home","Bounce the ball");
            }
        });

        button2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (HomeFragment.ServerIP.equals("") || HomeFragment.ServerPort.equals("")) {
                    return;
                }

                Log.d("Rectangle", "Sending Rectangle Request...");

                OkHttpClient client = new OkHttpClient();
                String url = "http://" + HomeFragment.ServerIP + ":" + HomeFragment.ServerPort + "/rectangle";

                Log.d("Rectangle", "URL: " + url);

                Request request = new Request.Builder().url(url).build();
                client.newCall(request).enqueue(new Callback() {
                    @Override
                    public void onFailure(Call call, IOException e) {
                        e.printStackTrace();
                    }
                    @Override
                    public void onResponse(Call call, Response response) throws IOException {
                    }
                });

                Log.d("Home","Draw Rectangle");
            }
        });

        button3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (HomeFragment.ServerIP.equals("") || HomeFragment.ServerPort.equals("")) {
                    return;
                }

                Log.d("Circle", "Sending Circle Request...");

                OkHttpClient client = new OkHttpClient();
                String url = "http://" + HomeFragment.ServerIP + ":" + HomeFragment.ServerPort + "/circle";

                Log.d("Circle", "URL: " + url);

                Request request = new Request.Builder().url(url).build();
                client.newCall(request).enqueue(new Callback() {
                    @Override
                    public void onFailure(Call call, IOException e) {
                        e.printStackTrace();
                    }
                    @Override
                    public void onResponse(Call call, Response response) throws IOException {
                    }
                });

                Log.d("Home","Draw Circle");
            }
        });

        titleText.setText("Ball Bouncer!");

        return v;
    }

    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);

        Thread thread = new Thread(new Runnable() {
            @Override
            public void run() {
                int counter = 0;
                while (true) {
                    if (counter < 10000000) {
                        counter++;
                        continue;
                    }

                    counter = 0;

                    Paint paint = new Paint();
                    paint.setColor(getResources().getColor(R.color.orange));
                    paint.setStyle(Paint.Style.FILL);

                    final Bitmap bitmap = Bitmap.createBitmap(500,500, Bitmap.Config.ARGB_8888);
                    Canvas canvas = new Canvas(bitmap);

                    getReq();

                    canvas.drawCircle(x, y, radius, paint);

                    ball.post(new Runnable() {
                        @Override
                        public void run() {
                            ball.setImageBitmap(bitmap);
                        }
                    });
                }
            }
        });

        thread.start();
    }

    @Override
    public void onActivityCreated(@Nullable Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);
        //show toolbar and make drawer enable
        ((DrawerLocker) getActivity()).setDrawerEnabled(true);
    }

    private void getReq(){
        if (HomeFragment.ServerIP.equals("")) {
            return;
        }

        if (HomeFragment.ServerPort.equals("")) {
            return;
        }
        OkHttpClient client = new OkHttpClient();
        String url = "http://" + HomeFragment.ServerIP + ":" + HomeFragment.ServerPort + "/ball";
        Request request = new Request.Builder()
                .url(url)
                .build();
        client.newCall(request).enqueue(new Callback() {
            @Override
            public void onFailure(Call call, IOException e) {
                e.printStackTrace();
            }
            @Override
            public void onResponse(Call call, Response response) throws IOException {
                if (response.isSuccessful()) {
                    final String myResponse = response.body().string();
                    String[] tokens = myResponse.split(",");
                    x = Integer.parseInt(tokens[0]);
                    y = Integer.parseInt(tokens[1]);
                    // radius = Integer.parseInt(tokens[2]);
                    radius = 50;
                }
            }
        });
    }
}
