<?xml version="1.0" encoding="UTF-8"?>
<tileset version="1.5" tiledversion="1.7.0" name="tileset" tilewidth="16" tileheight="16" tilecount="322" columns="23">
 <properties>
  <property name="tileset_prop" type="float" value="5.45"/>
 </properties>
 <image source="../tileset.png" width="368" height="224"/>
 <tile id="1" type="sdf"/>
 <tile id="2">
  <properties>
   <property name="tile_prop" type="bool" value="true"/>
  </properties>
 </tile>
 <tile id="15">
  <animation>
   <frame tileid="15" duration="105"/>
   <frame tileid="16" duration="105"/>
   <frame tileid="17" duration="105"/>
   <frame tileid="18" duration="105"/>
  </animation>
 </tile>
 <tile id="16">
  <animation>
   <frame tileid="16" duration="105"/>
   <frame tileid="17" duration="105"/>
   <frame tileid="18" duration="105"/>
   <frame tileid="15" duration="105"/>
  </animation>
 </tile>
 <tile id="17">
  <animation>
   <frame tileid="17" duration="105"/>
   <frame tileid="18" duration="105"/>
   <frame tileid="15" duration="105"/>
   <frame tileid="16" duration="105"/>
  </animation>
 </tile>
 <tile id="18">
  <animation>
   <frame tileid="18" duration="105"/>
   <frame tileid="15" duration="105"/>
   <frame tileid="16" duration="105"/>
   <frame tileid="17" duration="105"/>
  </animation>
 </tile>
 <tile id="60">
  <properties>
   <property name="prop" value="gezt"/>
  </properties>
  <animation>
   <frame tileid="60" duration="250"/>
   <frame tileid="83" duration="250"/>
  </animation>
 </tile>
 <tile id="84">
  <animation>
   <frame tileid="84" duration="250"/>
   <frame tileid="85" duration="250"/>
   <frame tileid="86" duration="250"/>
   <frame tileid="87" duration="250"/>
  </animation>
 </tile>
</tileset>
