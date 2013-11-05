#!/usr/bin/php

<?php
$buf = file_get_contents('site.html');
preg_match("#<title>([\w\s\-.]+?)</title>#", $buf , $matches);

print_r($matches);
?>
