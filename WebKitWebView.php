<?php

$webkit = new WebKitGtkWebView();
$webkit->open("saf");

var_dump($webkit->getMainFrame());

