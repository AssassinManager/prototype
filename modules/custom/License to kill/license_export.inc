<?php

/*
 * Exporting the license using Views Data Export
 */
function export_licenses_as_csv() {
    global $base_url;
    $page = $base_url . '/licenses-export';

    if (headers_sent()){
      die('<script type="text/javascript">window.location=\'' . $page . '\';</script>');
    }else{
      header("Location: " . $page);
      die();
    }
}