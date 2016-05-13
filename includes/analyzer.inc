<?php

/*
 * @params Collection $pid, Datastream type (MODS, DC)
 *
 * Test the PID to ensure it is a collection and query for all 
 * child objects.
 *
 *
 */


function islandora_get_missing_datastreams( $parentPID, $dataStream, $filepath ){

  $query = <<<EOQ
  SELECT ?pid FROM <#ri>
WHERE {
    {
  ?pid <fedora-rels-ext:isMemberOf> <info:fedora/$parentPID>
  }
  UNION
  {
  ?pid <fedora-rels-ext:isMemberOfCollection> <info:fedora/$parentPID>
  }
}
EOQ;
  $connection = islandora_get_tuque_connection();

  $sparql_count = $connection->repository->ri->countQuery($query, 'sparql');
  $results = $connection->repository->ri->sparqlQuery($query); 

  $in_list = array();
  $out_list = array();

  foreach ($results as $result) {
    $fedoraObject = islandora_object_load($result['pid']['value']);

    if(isset($fedoraObject[$dataStream])){
      $in_list[] = $fedoraObject->id;
    } else {
      $out_list[] = $fedoraObject->id;
    }
}

file_put_contents($filepath, "missing: " . implode(",", $out_list));
file_put_contents($filepath, "\nfound: " . implode(",", $in_list), FILE_APPEND);

}

?>