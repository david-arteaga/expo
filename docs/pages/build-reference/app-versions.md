---
title: App version management
---
import { Collapsible } from '~/ui/components/Collapsible';

Android and iOS each expose two values that identify the version of an application; one that is visible in stores, and another that is visible only to developers.

In managed projects, we use fields `version`/`android.versionCode`/`ios.buildNumber` in **app.json** to define versions, where `android.versionCode`/`ios.buildNumber` represents the developer-facing build version and `version` is the user-facing value visible in stores. For bare projects, each of those values maps to specific parts of the native configuration:

- [`version`][config-version] field in **app.json** on iOS represents `CFBundleShortVersionString` in **Info.plist**.
- [`version`][config-version] field in **app.json** on Android represents `versionName` in **android/app/build.gradle**.
- [`ios.buildNumber`][config-ios-buildnumber] field in **app.json** represents `CFBundleVersion` in **Info.plist**.
- [`android.versionCode`][config-android-versioncode] field in **app.json** represents `versionCode` in **android/app/build.gradle**.

One of the most frequent causes of app store rejections is submitting a build with a duplicate version number. This happens when a developer forgets to increment the version number prior to running a build.


EAS Build can manage automatically incrementing these versions for you if you opt in to using the "remote" app version source. The default behavior is to use a "local" app version source, which means you control versions manually in their respective config files.

To simplify the descriptions, we will use **app.json** terminology (`version`/`versionCode`/`buildNumber`) for the rest of this page, but unless stated otherwise, the same applies to bare projects.

## Examples

<Collapsible summary="Remote version source">

With this **eas.json**, the version for all builds will be based on the value stored on EAS servers, and the version will be incremented remotely and only when building with `production` profile.

```json
{
  "cli": {
    "appVersionSource": "remote"
  },
  "build": {
    "staging": {
      "distribution": "internal",
      "android": {
        "buildType": "apk"
      }
    },
    "production": {
      "autoIncrement": true
    }
  }
}
```

</Collapsible>

<Collapsible summary="Local version source">

With this **eas.json**, the version for all builds will be based on the value from **app.json** or native code. When you build using `production` profile, the version will be incremented in the local code before the build.

```json
{
  "cli": {
    "appVersionSource": "local"
  },
  "build": {
    "staging": {
      "distribution": "internal",
      "android": {
        "buildType": "apk"
      }
    },
    "production": {
      "autoIncrement": true
    }
  }
}
```

</Collapsible>

## Remote version source

You can configure your project to rely on EAS servers to store and manage the version of your app. Add `{ "cli": { "appVersionSource": "remote" } }` in your **eas.json**. The remote version will be initialized with the value from the local project. If you would like to explicitly set the value directly, or EAS CLI is not able to detect what version the app is on, you can use the `eas build:version:set` command. EAS stores version information scoped by account, slug, platform, and application ID/bundle identifier — so, for example, if you are building variants with different application IDs or bundle identifiers, versioning will be independent for each of them.

If you want to build your project locally in Android Studio or Xcode using the same version stored remotely on EAS, you can update your local project with the remote versions using `eas build:version:sync`.

Enabling the `autoIncrement` option in the remote app version source mode is currently only available for `versionCode`/`buildNumber`.

When using a remote app version source, the values in **app.json** will not be updated when the version is incremented remotely, and so the local and remote values will fall out of sync. The remote source values will be set on the native project when running a build, and they are the source of truth  — however, the values specified in your **app.json** will be present in `Constants.expoConfig` and `Constants.manifest` exposed by `expo-constants`. Use `expo-application` to determine your application version at runtime instead, and remove `versionCode`/`buildNumber` from your **app.json**.

### Limitations

- `eas build:version:sync` command on Android does not support bare projects with multiple flavors, but the rest of the remote versioning functionality should work with all projects.
- `autoIncrement` does not support the `version` option.
- It's not supported if you are using EAS Update and runtime policy set to `"runtimeVersion": { "policy": "nativeVersion" }`. For similar behavior, use the `"appVersion"` policy instead.

### Recommended workflow

The main goal of this feature is to avoid manual changes to the project every time you are uploading a new archive to run it on TestFlight/Play Store testing channels. When you are doing a production release, the user-facing version change should be explicit.

We recommend updating `version` field after a new build goes live in the store, especially if you are using `expo-updates` with an automatic runtime version policy. This marks the beginning of a new development cycle for a new version of your app. [Learn more about deployment patterns](/eas-update/deployment-patterns.md).

## Local version source

By default, the source of truth for project versions is the local project source code itself. In this case, EAS does not write to the project, it reads the values and builds projects as they are.

You may opt in to auto incrementing versions locally with the `autoIncrement` option on a build profile, but it comes with some limitations.

In the case of bare React Native projects, values in native code take precedence, and `expo-constants` and `expo-updates` read values from **app.json**. If you rely on version values from a manifest, you should keep them in sync with native code. Keeping these values in sync is especially important if you are using EAS Update with the runtime policy set to `"runtimeVersion": { "policy": "nativeVersion" }`, because mismatched versions may result in the delivery of updates to the wrong version of an application. We recommend using `expo-application` to read the version instead of depending on values from **app.json**.

### Limitations

- With `autoIncrement`, you need to commit your changes on every build if you want the version change to persist. This can be difficult to coordinate when building on CI.
- `autoIncrement` is not supported if you are using a dynamic config (**app.config.js**).
- For bare React Native projects with Gradle configuration that supports multiple flavors, EAS CLI is not able to read or modify the version, so `autoIncrement` option is not supported and versions will not be listed in the build details page on [expo.dev](https://expo.dev).


[config-version]: /versions/latest/config/app/#version
[config-android-versioncode]: /versions/latest/config/app/#versioncode
[config-ios-buildnumber]: /versions/latest/config/app/#buildnumber