<?php

/*
 * Programatically creating a license
 */
function create_license($number) {
    $node = new stdClass();
    $node->type = 'license_to_kill';
    node_object_prepare($node);

    $node->title = 'license-' . $number;
    $node->field_code['und'][0]['value'] = "0";

    node_save($node);
}

/*
 * Generating the code for the license
 */
function license_to_kill_node_presave($node) {   
    
    if ($node->type != 'license_to_kill') return;

    $code = module_invoke(genpass_algorithm_module(), 'password');

    if (!isset($node->field_license['und']) ||
        $node->field_license['und'][0]['value'] == "0") 
    {
        $node->field_license['und'][0]['value'] = $code;
    }
}