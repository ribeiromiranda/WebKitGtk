<?php


$webkit = new WebKitGtkWebView();

echo "before open WebKitGtkWebView::getEncoding() : {$webkit->getEncoding()}\n";

var_dump($webkit->open("http://www.google.com.br"));

echo "after open WebKitGtkWebView::getEncoding() : {$webkit->getEncoding()}\n";
$webframe = $webkit->getMainFrame();


$webDataSource = $webframe->getDataSource();

echo "\n";
$webFrame2 = $webDataSource->getWebFrame();
echo "WebKitGtkWebDataSource::getWebFrame: \n";
var_dump($webframe == $webFrame2);
echo "\n";

echo "WebKitGtkWebDataSource::getEncoding uri: " . $webDataSource->getEncoding() . "\n";
echo "WebKitGtkWebDataSource::getUnreachableUri uri: " . $webDataSource->getUnreachableUri() . "\n";
echo "WebKitGtkWebDataSource::getData len: " . strlen($webDataSource->getData()) . "\n";
echo "\n";

echo "WebKitGtkWebDataSource::getMainResource \n";
$mainResource = $webDataSource->getMainResource();
echo "WebKitGtkWebResource::getData: " . strlen($mainResource->getData()) . "\n";
echo "WebKitGtkWebResource::getMimeType: " . $mainResource->getMimeType() . "\n";
echo "WebKitGtkWebResource::getUri: " . $mainResource->getUri() . "\n";

echo "\n";

$subResources = $webDataSource->getSubResources();
echo "getSubRsource count: " . count($subResources) . "\n";

foreach ($subResources as $webResource) {
    echo "WebKitGtkWebResource::getData len: " . strlen($webResource->getData()) . "\n";
    echo "WebKitGtkWebResource::getEncoding: " . $webResource->getEncoding() . "\n";
    echo "WebKitGtkWebResource::getFrameName: " . $webResource->getFrameName() . "\n";
    echo "WebKitGtkWebResource::getMimeType: " . $webResource->getMimeType() . "\n";
    echo "WebKitGtkWebResource::getUri: " . $webResource->getUri() . "\n";

    echo "---------------------------- \n";
}
