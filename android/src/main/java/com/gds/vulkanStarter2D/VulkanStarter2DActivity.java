package com.gds.vulkanStarter2D;

import android.app.NativeActivity;
import android.os.Bundle;

/**
 * Created by czuber on 09/03/18.
 */

public class VulkanStarter2DActivity extends NativeActivity {

    static {
        System.loadLibrary("VulkanStarter2D");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        if (!isTaskRoot()) {
            finish();
            return;
        }

    }
}
