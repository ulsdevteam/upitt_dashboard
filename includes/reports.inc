<?php 

/** Unit to store the content functions related to each report 
 * 
 */


function upitt_dashboard_test1_content($csv = FALSE, $start = 0) {
  $subject = 'Orphan Page (BookCModel) report';
  module_load_include('inc', 'islandora_solr_search', 'includes/utilities');
  $query_processor = new IslandoraSolrQueryProcessor();
  $q = '(PID:pitt\:*) AND -RELS_EXT_isPageOf_uri_s:["" TO *] AND RELS_EXT_hasModel_uri_s:(*info\:fedora\/islandora\:pageCModel*)';
  $fq = "";
  $fl = "PID,fedora_datastreams_ms,isMemberOfSite,fgs_label_s,RELS_EXT_isMemberOfSite_uri_ms";
  $query_processor->solrQuery = $q;
  $query_processor->solrStart = 0;
  $query_processor->solrLimit = 1000;
  $query_processor->solrParams = array(
    'fl' => $fl,
    'fq' => $fq,
  );
  $headings = array('PID' => 'PID',
                    'fgs_label_s' => 'Fedora Label',
                    'RELS_EXT_isMemberOfSite_uri_ms' => 'Member of Sites',
                    'fedora_datastreams_ms' => 'Datastreams');
  $url = parse_url(variable_get('islandora_solr_url', 'localhost:8080/solr'));
  $solr = new Apache_Solr_Service($url['host'], $url['port'], $url['path'] . '/');
  $solr->setCreateDocuments(FALSE);
  $results = array();
  try {
    $search_results = $solr->search($query_processor->solrQuery, $query_processor->solrStart, $query_processor->solrLimit, $query_processor->solrParams, 'GET');
    $tmp = json_decode($search_results->getRawResponse(), TRUE);
    if ($tmp['response']['numFound'] > 0) {
      foreach ($tmp['response']['docs'] as $rec) {
        if (isset($rec['PID']) && isset($rec['fgs_label_s']) && !$csv) {
          $rec['PID'] = l($rec['PID'], '/islandora/object/' . $rec['PID']);
        }
        $rec['RELS_EXT_isMemberOfSite_uri_ms'] = implode(", ", $rec['RELS_EXT_isMemberOfSite_uri_ms']);
        $rec['fedora_datastreams_ms'] = implode(", ", $rec['fedora_datastreams_ms']);
        $results[] = $rec;
      }
    }
  }
  catch (Exception $e) {
  }

  $search_link = ""; //l(t('Results as Search'), '/islandora/search?islandora_solr_search_navigation=0&f[0]=' . $q . '&f[1]=' . $fq);
  $download_csv = l(t('Download CSV'), 'upitt_dashboard/report_block/test1/downloadcsv');
  if (!$csv) {
    $content = theme('data_table_wrapper', array('rows' => $results, 'download_csv' => $download_csv, 'search_link' => $search_link)) .
      theme('table', array('header' => $headings, 'rows' => $results));
  } else {
    $filename = tempnam('/tmp', 'CSV_');
    $fp = fopen($filename, 'w');
    fputcsv($fp, $headings);
    foreach ($results as $fields) {
      fputcsv($fp, $fields);
    }
    fclose($fp);
    $content = file($filename);
    unset($filename);
  }
  return array($subject, $content);
}

function upitt_dashboard_test2_content($csv = FALSE, $start = 0) {
  $subject = 'WebServices needs to add TN_LARGE';
  module_load_include('inc', 'islandora_solr_search', 'includes/utilities');
  $query_processor = new IslandoraSolrQueryProcessor();
  $q = '(PID:pitt\:*) AND (RELS_EXT_hasModel_uri_s:info\:fedora\/islandora\:bookCModel)';
  $fq = "-fedora_datastream_latest_TN_LARGE_ID_ms:[* TO *]";
  $fl = "PID,fedora_datastreams_ms,isMemberOfSite,fgs_label_s,RELS_EXT_isMemberOfSite_uri_ms";
  $query_processor->solrQuery = $q;
  $query_processor->solrStart = 0;
  $query_processor->solrLimit = 1000;
  $query_processor->solrParams = array(
    'fl' => $fl,
    'fq' => $fq,
  );
  $headings = array('PID' => 'PID',
                    'fgs_label_s' => 'Fedora Label',
                    'RELS_EXT_isMemberOfSite_uri_ms' => 'Member of Sites',
                    'fedora_datastreams_ms' => 'Datastreams');
  $url = parse_url(variable_get('islandora_solr_url', 'localhost:8080/solr'));
  $solr = new Apache_Solr_Service($url['host'], $url['port'], $url['path'] . '/');
  $solr->setCreateDocuments(FALSE);
  $results = array();
  try {
    $search_results = $solr->search($query_processor->solrQuery, $query_processor->solrStart, $query_processor->solrLimit, $query_processor->solrParams, 'GET');
    $tmp = json_decode($search_results->getRawResponse(), TRUE);
    if ($tmp['response']['numFound'] > 0) {
      foreach ($tmp['response']['docs'] as $rec) {
        if (isset($rec['PID']) && isset($rec['fgs_label_s']) && !$csv) {
          $rec['PID'] = l($rec['PID'], '/islandora/object/' . $rec['PID']);
        }
        $rec['RELS_EXT_isMemberOfSite_uri_ms'] = implode(", ", $rec['RELS_EXT_isMemberOfSite_uri_ms']);
        $rec['fedora_datastreams_ms'] = implode(", ", $rec['fedora_datastreams_ms']);
        $results[] = $rec;
      }
    }
  }
  catch (Exception $e) {
  }
  $search_link = ""; //l(t('Results as Search'), sprintf('islandora/search?islandora_solr_search_navigation=0&f[0]=%s*&f[1]=%s', $q, $fq));
  $download_csv = l(t('Download CSV'), 'upitt_dashboard/report_block/test2/downloadcsv');
  if (!$csv) {
    $content = theme('data_table_wrapper', array('rows' => $results, 'download_csv' => $download_csv, 'search_link' => $search_link)) . 
      theme('table', array('header' => $headings, 'rows' => $results));
  } else {
    $filename = tempnam('/tmp', 'CSV_');
    $fp = fopen($filename, 'w');
    fputcsv($fp, $headings);
    foreach ($results as $fields) {
      fputcsv($fp, $fields);
    }
    fclose($fp);
    $content = file($filename);
    unset($filename);
  }
  return array($subject, $content);
}

function upitt_dashboard_orphanManuscript_content($csv = FALSE, $start = 0) {
  $subject = 'Orphan manuscript ("Book")';
  module_load_include('inc', 'islandora_solr_search', 'includes/utilities');
  $query_processor = new IslandoraSolrQueryProcessor();
  $q = '(PID:pitt\:*) AND -RELS_EXT_isMemberOfCollection_uri_s:["" TO *] AND RELS_EXT_hasModel_uri_s:(*info\:fedora\/islandora\:bookCModel*)';
  $fq = "";
  $fl = "PID,RELS_EXT_hasModel_uri_ms,RELS_EXT_isMemberOfSite_uri_ms,fgs_label_s";
  $query_processor->solrQuery = $q;
  $query_processor->solrStart = 0;
  $query_processor->solrLimit = 10000;
  $query_processor->solrParams = array(
    'fl' => $fl,
    'fq' => $fq,
  );
  $headings = array('PID' => 'PID',
                    'fgs_label_s' => 'Fedora Label',
                    'RELS_EXT_hasModel_uri_ms' => 'Model/s',
                    'RELS_EXT_isMemberOfSite_uri_ms' => 'Member of Sites');
  $url = parse_url(variable_get('islandora_solr_url', 'localhost:8080/solr'));
  $solr = new Apache_Solr_Service($url['host'], $url['port'], $url['path'] . '/');
  $solr->setCreateDocuments(FALSE);
  $results = array();
  try {
    $search_results = $solr->search($query_processor->solrQuery, $query_processor->solrStart, $query_processor->solrLimit, $query_processor->solrParams, 'GET');
    $tmp = json_decode($search_results->getRawResponse(), TRUE);
    if ($tmp['response']['numFound'] > 0) {
      foreach ($tmp['response']['docs'] as $rec) {
        if (isset($rec['PID']) && isset($rec['fgs_label_s']) && !$csv) {
          $rec['PID'] = l($rec['PID'], '/islandora/object/' . $rec['PID']);
        }
        $rec['RELS_EXT_hasModel_uri_ms'] = implode(", ", $rec['RELS_EXT_hasModel_uri_ms']);
        $rec['RELS_EXT_isMemberOfSite_uri_ms'] = implode(", ", $rec['RELS_EXT_isMemberOfSite_uri_ms']);
        $results[] = $rec;
      }
    }
  }
  catch (Exception $e) {
  }
  $search_link = ""; //l(t('Results as Search'), sprintf('islandora/search?islandora_solr_search_navigation=0&f[0]=%s*&f[1]=%s', $q, $fq));
  $download_csv = l(t('Download CSV'), 'upitt_dashboard/report_block/orphanManuscript/downloadcsv');
  if (!$csv) {
    $content = theme('data_table_wrapper', array('rows' => $results, 'download_csv' => $download_csv, 'search_link' => $search_link)) .
      theme('table', array('header' => $headings, 'rows' => $results));
  } else {
    $filename = tempnam('/tmp', 'CSV_');
    $fp = fopen($filename, 'w');
    fputcsv($fp, $headings);
    foreach ($results as $fields) {
      fputcsv($fp, $fields);
    }
    fclose($fp);
    $content = file($filename);
    unset($filename);
  }
  return array($subject, $content);
}

