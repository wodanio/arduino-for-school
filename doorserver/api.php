<?php

require_once( 'config.inc.php' );

$db = new mysqli( DSConfig::$dbHost, DSConfig::$dbUser, DSConfig::$dbPasswd, DSConfig::$dbDatabase );
if ( $db->connect_errno )
    die("Kein DBdatenbankverbindung.");

if ( checkGetField('token') && checkGetField('rfid_token') ) {
    $token = $_GET['token'];
    $rfid_token = $_GET['rfid_token'];

    $result = $db->query( 'SELECT * FROM api_tokens WHERE token = \'' . $token . '\'' );
    
    if ( $result->num_rows > 0 && $result->fetch_object()->access == true ) {

        $result = $db->query( 'SELECT * FROM access_keys WHERE rfid_key = \'' . $rfid_token . '\'' );
        if ( $result->num_rows > 0 ) {
            $resval = $result->fetch_object();
            if ( $resval->access == true )
                returnResult( true, 'The Card has Access', array(
                    'access'    => true,
                    'data'      => $resval
                ) );
        }
        returnResult( true, 'The Card has not Access', array(
            'access'    => false,
            'data'      => null
        ) );

    } else
        returnResult( false, 'No Access' );

} else 
    returnResult( false, 'No Attr in URL' );

function getSQLData ( $sql ) {
    return $db->query( $sql );
}

function returnResult( $status, $desc, $value = null ) {
    $string = json_encode(array(
        'status'        => $status,
        'desc'          => $desc,
        'value'         => $value,
        'meta'          => array(
            'date'      => date('Y-m-d'),
            'time'      => date('H:i:s')
        )
    ));
    print( $string );
    die();
}

function checkGetField ( $name ) {
    return ( isset($_GET[$name]) && !empty($_GET[$name]) ) ? true : false;
}