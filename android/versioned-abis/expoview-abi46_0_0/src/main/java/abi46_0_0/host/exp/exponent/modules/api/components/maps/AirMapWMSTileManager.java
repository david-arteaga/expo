package abi46_0_0.host.exp.exponent.modules.api.components.maps;

import android.content.Context;
import android.os.Build;
import android.util.DisplayMetrics;
import android.view.WindowManager;

import abi46_0_0.com.facebook.react.bridge.ReactApplicationContext;
import abi46_0_0.com.facebook.react.uimanager.ThemedReactContext;
import abi46_0_0.com.facebook.react.uimanager.ViewGroupManager;
import abi46_0_0.com.facebook.react.uimanager.annotations.ReactProp;

public class AirMapWMSTileManager extends ViewGroupManager<AirMapWMSTile> {
  private DisplayMetrics metrics;

  public AirMapWMSTileManager(ReactApplicationContext reactContext) {
    super();
    if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.JELLY_BEAN_MR1) {
      metrics = new DisplayMetrics();
      ((WindowManager) reactContext.getSystemService(Context.WINDOW_SERVICE))
          .getDefaultDisplay()
          .getRealMetrics(metrics);
    } else {
      metrics = reactContext.getResources().getDisplayMetrics();
    }
  }

  @Override
  public String getName() {
    return "AIRMapWMSTile";
  }

  @Override
  public AirMapWMSTile createViewInstance(ThemedReactContext context) {
    return new AirMapWMSTile(context);
  }

  @ReactProp(name = "urlTemplate")
  public void setUrlTemplate(AirMapWMSTile view, String urlTemplate) {
    view.setUrlTemplate(urlTemplate);
  }

  @ReactProp(name = "zIndex", defaultFloat = -1.0f)
  public void setZIndex(AirMapWMSTile view, float zIndex) {
    view.setZIndex(zIndex);
  }

  @ReactProp(name = "minimumZ", defaultFloat = 0.0f)
  public void setMinimumZ(AirMapWMSTile view, float minimumZ) {
    view.setMinimumZ(minimumZ);
  }

  @ReactProp(name = "maximumZ", defaultFloat = 100.0f)
  public void setMaximumZ(AirMapWMSTile view, float maximumZ) {
    view.setMaximumZ(maximumZ);
  }

  @ReactProp(name = "maximumNativeZ", defaultFloat = 100.0f)
  public void setMaximumNativeZ(AirMapWMSTile view, float maximumNativeZ) {
    view.setMaximumNativeZ(maximumNativeZ);
  }

  @ReactProp(name = "tileSize", defaultFloat = 256.0f)
  public void setTileSize(AirMapWMSTile view, float tileSize) {
    view.setTileSize(tileSize);
  }

  @ReactProp(name = "tileCachePath")
  public void setTileCachePath(AirMapWMSTile view, String tileCachePath) {
    view.setTileCachePath(tileCachePath);
  }

  @ReactProp(name = "tileCacheMaxAge", defaultFloat = 0.0f)
  public void setTileCacheMaxAge(AirMapWMSTile view, float tileCacheMaxAge) {
    view.setTileCacheMaxAge(tileCacheMaxAge);
  }

  @ReactProp(name = "offlineMode", defaultBoolean = false)
  public void setOfflineMode(AirMapWMSTile view, boolean offlineMode) {
    view.setOfflineMode(offlineMode);
  }

  @ReactProp(name = "opacity", defaultFloat = 1.0f)
  public void setOpacity(AirMapWMSTile view, float opacity) {
    view.setOpacity(opacity);
  }
}
