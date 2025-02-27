package abi45_0_0.host.exp.exponent.modules.api.screens.events

import abi45_0_0.com.facebook.react.bridge.Arguments
import abi45_0_0.com.facebook.react.uimanager.events.Event
import abi45_0_0.com.facebook.react.uimanager.events.RCTEventEmitter

class ScreenTransitionProgressEvent(
  viewId: Int,
  private val mProgress: Float,
  private val mClosing: Boolean,
  private val mGoingForward: Boolean,
  private val mCoalescingKey: Short
) : Event<ScreenAppearEvent?>(viewId) {
  override fun getEventName(): String {
    return EVENT_NAME
  }

  override fun getCoalescingKey(): Short {
    return mCoalescingKey
  }

  override fun dispatch(rctEventEmitter: RCTEventEmitter) {
    val map = Arguments.createMap()
    map.putDouble("progress", mProgress.toDouble())
    map.putInt("closing", if (mClosing) 1 else 0)
    map.putInt("goingForward", if (mGoingForward) 1 else 0)
    rctEventEmitter.receiveEvent(viewTag, eventName, map)
  }

  companion object {
    const val EVENT_NAME = "topTransitionProgress"
  }
}
