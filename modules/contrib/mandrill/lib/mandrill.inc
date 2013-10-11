<?php

/**
 * @file
 * Wrapper class around the Mandrill API.
 */

/**
 * Class Mandrill.
 */
class DrupalMandrill extends Mandrill {

  /**
   * Override Mandrill constructor since we are not using CURL.
   *
   * @string $apikey
   * @int $timeout
   */
  public function __construct($apikey, $timeout = 60) {
    if (!$apikey) {
      throw new Mandrill_Error('You must provide a Mandrill API key');
    }
    $this->apikey = $apikey;
    $this->timeout = 60;

    $this->templates = new Mandrill_Templates($this);
    $this->exports = new Mandrill_Exports($this);
    $this->users = new Mandrill_Users($this);
    $this->rejects = new Mandrill_Rejects($this);
    $this->inbound = new Mandrill_Inbound($this);
    $this->tags = new Mandrill_Tags($this);
    $this->messages = new Mandrill_Messages($this);
    $this->whitelists = new Mandrill_Whitelists($this);
    $this->ips = new Mandrill_Ips($this);
    $this->internal = new Mandrill_Internal($this);
    $this->subaccounts = new Mandrill_Subaccounts($this);
    $this->urls = new Mandrill_Urls($this);
    $this->webhooks = new Mandrill_Webhooks($this);
    $this->senders = new Mandrill_Senders($this);
  }

  /**
   * Override the call method to use Drupal's HTTP handling.
   *
   * @string $url
   * @array $params
   *
   * @return mixed
   *   Mandrill response as an associative array.
   * @throws Mandrill_Error
   * @throws Mandrill_HttpError
   */
  public function call($url, $params) {
    $params['key'] = $this->apikey;
    $params = drupal_json_encode($params);

    $options = array(
      'headers' => array(
        'Content-Type' => 'application/json',
        'USERAGENT' => 'Mandrill-PHP/1.0.48',
      ),
      'data' => $params,
      'method' => 'POST',
      'timeout' => $this->timeout,
    );
    $response = drupal_http_request($this->root . '/' . $url . '.json', $options);

    if (empty($response)) {
      throw new Mandrill_HttpError("API call to $url failed to return a response.");
    }
    if (floor($response->code / 100) >= 4) {
      throw new Mandrill_HttpError($response->status_message, $response->code);
    }
    if (!empty($response->error)) {
      throw new Mandrill_HttpError("API call to $url failed: " . $response->error);
    }
    $result = drupal_json_decode($response->data);
    if ($result === NULL) {
      throw new Mandrill_Error('We were unable to decode the JSON response from the Mandrill API: ' . $response->data);
    }

    return $result;
  }

  /**
   * Return an array structure for a message attachment.
   *
   * @param string $path
   *   Attachment path.
   *
   * @return array
   *   Attachment structure.
   *
   * @throws Mandrill_Error
   * @throws Exception
   */
  public static function getAttachmentStruct($path) {
    $struct = array();

    try {

      if (!@is_file($path)) {
        throw new Exception($path . ' is not a valid file.');
      }

      $filename = basename($path);

      if (!function_exists('get_magic_quotes')) {
        function get_magic_quotes() {
          return FALSE;
        }
      }
      if (!function_exists('set_magic_quotes')) {
        function set_magic_quotes($value) {
          return TRUE;
        }
      }

      if (strnatcmp(phpversion(), '6') >= 0) {
        $magic_quotes = get_magic_quotes_runtime();
        set_magic_quotes_runtime(0);
      }

      $file_buffer = file_get_contents($path);
      $file_buffer = chunk_split(base64_encode($file_buffer), 76, "\n");

      if (strnatcmp(phpversion(), '6') >= 0) {
        set_magic_quotes_runtime($magic_quotes);
      }

      $mime_type = file_get_mimetype($path);
      if (!self::isValidContentType($mime_type)) {
        throw new Exception($mime_type . ' is not a valid content type (it should be ' . implode('*,', self::getValidContentTypes()) . ').');
      }

      $struct['type'] = $mime_type;
      $struct['name'] = $filename;
      $struct['content'] = $file_buffer;

    }
    catch (Exception $e) {
      throw new Mandrill_Error('Error creating the attachment structure: ' . $e->getMessage());
    }

    return $struct;
  }

  /**
   * Helper to determine attachment is valid.
   *
   * @static
   *
   * @param $ct
   *
   * @return bool
   */
  protected static function isValidContentType($ct) {
    foreach (self::getValidContentTypes() as $vct) {
      if (strpos($ct, $vct) !== FALSE) {
        return TRUE;
      }
    }

    return FALSE;
  }

  /**
   * Return an array of valid content types.
   *
   * @static
   *
   * @return array
   *   Valid content types to attach to an email.
   */
  protected static function getValidContentTypes() {
    $valid_types = array(
      'image/',
      'text/',
      'application/pdf',
      'application/x-zip',
    );
    drupal_alter('mandrill_valid_attachment_types', $valid_types);
    return $valid_types;
  }

}
