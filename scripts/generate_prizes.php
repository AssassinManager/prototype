<?php

_create_prizes(5);
print("Creating prizes\n");

function _generate_word($length){
  mt_srand((double)microtime()*1000000);

  $vowels = array("a", "e", "i", "o", "u");
  $cons = array("b", "c", "d", "g", "h", "j", "k", "l", "m", "n", "p", "r", "s", "t", "u", "v", "w", "tr",
  "cr", "br", "fr", "th", "dr", "ch", "ph", "wr", "st", "sp", "sw", "pr", "sl", "cl", "sh");

  $num_vowels = count($vowels);
  $num_cons = count($cons);
  $word = '';

  while(strlen($word) < $length){
    $word .= $cons[mt_rand(0, $num_cons - 1)] . $vowels[mt_rand(0, $num_vowels - 1)];
  }

  return substr($word, 0, $length);
}

function _create_prizes($num) {

  $prizes = array();
  while (count($prizes) < $num) {
    $prize = _generate_word(mt_rand(6, 12));
    $prizes[$prize] = '';
  }

  foreach ($prizes as $prize => $value) {
  	$node = new stdClass();
    $node->type = 'prize';
    node_object_prepare($node);

    $node->title = $prize;
    $node->field_prize_description['und'][0]['value'] = "Get the " . $prize . '!';

    node_save($node);
  }
}

?>