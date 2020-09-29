package com.app.ballbouncer;

import android.content.Intent;
import android.os.Bundle;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ProgressBar;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;

import java.util.Objects;
import java.util.Timer;
import java.util.TimerTask;

public class LoadingFragment extends Fragment {
    private int counter = 0;

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View v = inflater.inflate(R.layout.fragment_loading,container,false);
        //maybe modify some components
        return v;
    }

    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        progressBarLoading(view);
    }

    // to display progress bar as loading bar in loading page
    private void progressBarLoading(View v){

        final ProgressBar pb = v.findViewById(R.id.progressBar);
        final Timer t = new Timer();
        TimerTask tt = new TimerTask() {
            @Override
            public void run(){
                ++counter;
                pb.setProgress(counter);
                if(counter == 100) {
                    t.cancel();
                    //splash screen done, go to home fragment
                    FragmentManager fm = Objects.requireNonNull(getActivity()).getSupportFragmentManager();
                    FragmentTransaction ft = fm.beginTransaction();
                    ft.replace(R.id.fragment_container,new LoginFragment()).commit();
                }
            }
        };
        t.schedule(tt,0,10);

    }
}
