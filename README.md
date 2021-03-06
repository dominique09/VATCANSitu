# VATCANSitu

VATCANSitu is a EuroScope Plugin to simulate tools from NAVCANsuite

The author of this plugin has NO AFFILIATION with NavCanada. This tool is for simulation use only on the VATSIM network and not for real world aviation. 

The latest nightly build is available at appveyor (click the badge below, then "Artifact" and download the dll). Will have the most up to date development features.

New features in the continuous integration build and not in 0.3.1.2:
* ADSB capable aircraft outside of radar coverage display as an ADS-B PPS with modifiable datatags.
* SFI and controller remark handling (see wiki)
* Assigned speed and mach now displayed in data tag and assignable by right or left clicking the ground speed.

[![Build status](https://ci.appveyor.com/api/projects/status/github/ronyan/VATCANSitu?branch=master)](https://ci.appveyor.com/project/ronyan/vatcansitu)


### Latest Version 0.3.1.2 NOV23-2020
1. (NEW) Radar target tags are now drawn by the plugin. Tag functions remain in click spots from stock Canscope installs to facilitate an easier transition. Please note, I cannot find examples of direct-to and temp headings displayed in the tags of reference material I have access to, as such these are not shown (but you can assign them using the click spot or scractpad box to label for other controllers).
  * Tag connectors are now drawn with a dogleg in a similar style to the real scope. ADSB capable aircraft will display a small circle at the elbow.
  * Datatags now 'wink' during squawk ident and handoff events
  * Handoff tag handling behaviour modelled. Aircraft handed off to you will have its tag wink. After handoff, tags will wink and then revert to a "Bravo Tag" (less detailed) automatically. An option in the real software is to enable "H/O Persist" (planned for next version to allow you to choose).
  * Scratchpad content with one or two characters displays on line 1 as the SFI (one letter field after the callsign used by some FIRs). Longer scratchpad strings display on the last line of tag as "Controller Rermarks". 
2. (NEW) Quick Look button is now functional. Data tags moved during quick look will remain open. 
3. (NEW) Show "All" targets now a functional button.
4. (NEW) PTL drawn in a green colour now implemented (fixed at 3 mins at the moment).
5. (UPDATED) CJS during handoff events have been tweaked and no longer show the frequency (this behaviour was clarified using new source material.
6. (UPDATED) CJS will now wink white during a H/O warning event rather than disappear and reappear.
7. (UPDATED) CTP specific feature removed, will be a separate plugin for future events.

WIP features for the next update:
1. Configuration for tags and H/O Persist and H/O warn.
2. Flights of interest (FOI) will show with an alpha tag -- "A flight of Interest. A flight of Interest (FOI) is a target that is not yet
under the jurisdiction of this workstation, ... but this Master sector will be the first internal sector to have jurisdiction for the flight of Interest. The flight will not be affected by altitude filters."
3. PTL: currently crudely drawn using euclidean geometry, will be refactored and adjustable in 0.3.2.x


Installation notes: Disable the default ES symbology for correlated targets in the symbology settings by replacing with the line "MOVETO 0 0", use the Tag Editor to change ES default tags to "Static Line" as the only entry to avoid double tags.

# CHANGELOG
#### 0.2.4.5a
- RVSM aircraft will show with the diamond PPS symbology. 
- Primary targets will show in magenta.
- Squawk 7600 and 7700 will show a red triangle.
- Aircrafts identing will have their PPS flash instead of the unusual ES target.
- CJS will flash if aircraft are nearing your airspace border to remind you to hand-off (I believe an option on the real thing)
- FP predicted tracks show with the appropriate orange airplane symbol.
- Altitude filter will be on by default.

#### version 0.2.3
- Added altitude filter settings, and altitude filter toggle. Only works for tags draw for by the plugin (i.e. the VFR tags) since there is no way to hook directly into the ES default filters. Saves settings to sector files. 

#### version 0.2.1: AUG3
- hotfix for 0.2 retargetted character encoding for better compatibility
- Added the range display
- Added Controller jurisdiction symbol that updates depending on the position you log in as.

![Screenshot](https://i.imgur.com/CKYPSyb.png)

Compatible with Euroscope beta r24 or higher (plugin was compiled using VS toolset 2019)
https://www.euroscope.hu/wp/2020/04/12/3-2-1-24/

EuroScope Plugin to simulate tools from NAVCANsuite.

The author of this plugin has NO affiliation with Nav Canada; This tool is for simulation use only on the VATSIM network, not for real world aviation. 

https://vimeo.com/443838489

# Features
1. Correlated radar targets with a VFR flight plan will be shown using an orange present position symbol.
2. Halo tool allows rings to be drawn around specific aircraft. The built in function in ES draws around all planes and there's no way to only apply rings to specific planes.
3. Mouse halo tool to aid with separation. (please see known issues)
4. Range displayed in menu per the real scope
5. CJS button shows your logged in position
6. RVSM aircraft will show with the diamond PPS symbology. 
7. Primary targets will show in magenta.
8. Squawk 7600 and 7700 will show a red triangle.
9. Aircrafts identing will have their PPS flash instead of the unusual ES target.
10. CJS will flash if aircraft are nearing your airspace border to remind you to hand-off.
11. FP predicted tracks show with the appropriate orange airplane symbol.

Not implemented for now: There are some sham buttons just to replicate the UI (also I don't know what some of them do in the real system). RBL default ES tools work well, unlikely will be a priority.

# Installation
The dll was compiled using Visual Studio 2019 (v142) using MFC libraries. The source code is provided to allow you to review and compile yourself.

If you opt not to compile yourself, binaries are under releases. Load the .dll using the Plug-ins folder in EuroScope. Allow the plugin to draw on the "Standard ES radar screen"

# Known Issues
EuroScope runs at a very low framerate unless a function asks for more screen draws. Essentially runs at 1FPS most of the time! The RBL is an example of this; when it is called, the screen refreshes much quicker to make it follow your mouse and give you a smooth experience. This is quite taxing on CPU usage; try drawing a RBL line and spinning it around it a circle (CPU use will rise dramatically). To get smooth mouse tracking of the mouse halo, the plugin does the same thing. CPU use will be quite high when it is on, so I recommend turning it on only when needed. When the mouse halo is on, it may interfere with your ability to open up other ES windows (RWY selection, ATIS), so turn it off before opening these other windows.

(partially resolved with altitude filters v0.2.3)
If you use NARDS tags for ground operations, the VFR PPS symbol will show on top of the plane logo. Can potentially be resolved by adding an additional variable to the .asr fil (not yet implemented) VFR PPS symbols ignore altitude filters (I've emailed the developer of ES, unfortunately the PlugIn enviroment does not allow access to these built-in data). Fixing this would involve making another altitude filter function within the plugin, but this seems redudant...
