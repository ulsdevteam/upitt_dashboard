<?php

/** Unit to store the content functions related to each report
 *
 */

define('CST_ITEMS_PER_PAGE', 20);

function upitt_dashboard_test1_content($csv = FALSE, $page = 0) {
  $delta = 'test1';
  $subject = 'Orphan Page (BookCModel) report';
  $q = '(PID:pitt\:*) AND -RELS_EXT_isPageOf_uri_s:["" TO *] AND RELS_EXT_hasModel_uri_s:(*info\:fedora\/islandora\:pageCModel*)';
  $fq = "";
  $fl = "PID,fedora_datastreams_ms,fgs_label_s,RELS_EXT_isMemberOfSite_uri_ms";
  $headings = array('PID' => 'PID',
                    'fgs_label_s' => 'Fedora Label',
                    'RELS_EXT_isMemberOfSite_uri_ms' => 'Member of Sites',
                    'fedora_datastreams_ms' => 'Datastreams');
  return _get_SOLR_report($delta, $subject, $q, $fq, $fl, $headings, $csv, $page);
}

function upitt_dashboard_test2_content($csv = FALSE, $page = 0) {
  $delta = 'test2';
  $subject = 'WebServices needs to add TN_LARGE';
  $q = '(PID:pitt\:*) AND (RELS_EXT_hasModel_uri_s:info\:fedora\/islandora\:bookCModel)';
  $fq = "-fedora_datastream_latest_TN_LARGE_ID_ms:[* TO *]";
  $fl = "PID,fedora_datastreams_ms,fgs_label_s,RELS_EXT_isMemberOfSite_uri_ms";
  $headings = array('PID' => 'PID',
                    'fgs_label_s' => 'Fedora Label',
                    'RELS_EXT_isMemberOfSite_uri_ms' => 'Member of Sites',
                    'fedora_datastreams_ms' => 'Datastreams');

  return _get_SOLR_report($delta, $subject, $q, $fq, $fl, $headings, $csv, $page);
}

function upitt_dashboard_orphanManuscript_content($csv = FALSE, $page = 0) {
  $delta = 'orphanManuscript';
  $subject = 'Orphan manuscript ("Book")';
  $q = '(PID:pitt\:*) AND -RELS_EXT_isMemberOfCollection_uri_s:["" TO *] AND RELS_EXT_hasModel_uri_s:(*info\:fedora\/islandora\:bookCModel*)';
  $fq = "";
  $fl = "PID,RELS_EXT_hasModel_uri_ms,RELS_EXT_isMemberOfSite_uri_ms,fgs_label_s";
  $headings = array('PID' => 'PID',
                    'fgs_label_s' => 'Fedora Label',
                    'RELS_EXT_hasModel_uri_ms' => 'Model/s',
                    'RELS_EXT_isMemberOfSite_uri_ms' => 'Member of Sites');
  return _get_SOLR_report($delta, $subject, $q, $fq, $fl, $headings, $csv, $page);
}

/**
 * This returns the block-themed $subject, $content based on the report
 * parameters.  This is called by the upitt_dashboard_block_view code by a
 * dynamically created function name that corresponds to the block delta like
 * upitt_dashboard_{BLOCK_DELTA}_content.
 *
 * @param type $delta - block identifier.
 * @param type $subject - Title of the block
 * @param type $q - SOLR q "query" part of the query
 * @param type $fq - SOLR fq "filter query" part of the query
 * @param type $fl - SOLR fl "field list" part of the query
 * @param type $headings - array of SOLR fieldnames and the titles for those
 *               to use for the table output.
 * @param type $csv - TRUE / FALSE - whether or not the output should be CSV.
 * @param type $page - which page of the data the report is pulling, uses
 *               CST_ITEMS_PER_PAGE to calculate solr "start" value
 * @return type array of themed block content and the block subject
 */
function _get_SOLR_report($delta, $subject, $q, $fq, $fl, $headings, $csv, $page) {
  $num_found = _get_numFound($q, $fq, $fl);
  $pager_element = 0;
  $x = pager_default_initialize($num_items, CST_ITEMS_PER_PAGE, $pager_element);
  error_log('pager x = ' . $x . ', page = ' .$page);

  module_load_include('inc', 'islandora_solr_search', 'includes/utilities');
  $query_processor = new IslandoraSolrQueryProcessor();
  $query_processor->solrQuery = $q;
  $query_processor->solrStart = CST_ITEMS_PER_PAGE * $page;
  $query_processor->solrLimit = CST_ITEMS_PER_PAGE;
  $query_processor->solrParams = array(
    'fl' => $fl,
    'fq' => $fq,
  );
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

        foreach ($rec as $key=>$val) {
          if (is_array($rec[$key])) {
            $rec[$key] = implode(", ", $rec[$key]);
          }
        }
        $results[] = $rec;
      }
    }
  }
  catch (Exception $e) {
  }

  $search_link = ""; //l(t('Results as Search'), '/islandora/search?islandora_solr_search_navigation=0&f[0]=' . $q . '&f[1]=' . $fq);
  if (!$csv) {
    $download_csv = l(t('Download CSV'), 'upitt_dashboard/report_block/' . $delta . '/downloadcsv');
    $paging = theme('pager', array('element' => $pager_element));
error_log('paging = ' . print_r($paging, true));
    $table = theme('table', array('header' => $headings, 'rows' => $results));
    $content = theme('data_table_wrapper',
      array('rows' => $results,
            'download_csv' => $download_csv,
            'search_link' => $search_link, 'num_found' => $num_found, 'paging'=>$paging, 'table' => $table));
  } else {
    $filename = tempnam('/tmp', 'CSV_');
    $fp = fopen($filename, 'w');
    fputcsv($fp, $headings);
    foreach ($results as $fields) {
      fputcsv($fp, $fields);
    }
    fclose($fp);
    $content = file($filename);
    @unlink($filename);
  }
  return array($subject, $content, $num_found);
}

function _get_numFound($q, $fq, $fl) {
  module_load_include('inc', 'islandora_solr_search', 'includes/utilities');
  $query_processor = new IslandoraSolrQueryProcessor();
  $query_processor->solrQuery = $q;
  $query_processor->solrStart = 0;
  $query_processor->solrLimit = 1;
  $query_processor->solrParams = array(
    'fl' => $fl,
    'fq' => $fq,
  );
  $url = parse_url(variable_get('islandora_solr_url', 'localhost:8080/solr'));
  $solr = new Apache_Solr_Service($url['host'], $url['port'], $url['path'] . '/');
  $solr->setCreateDocuments(FALSE);
  $num_found = 0;
  try {
    $search_results = $solr->search($query_processor->solrQuery, $query_processor->solrStart, $query_processor->solrLimit, $query_processor->solrParams, 'GET');
    $tmp = json_decode($search_results->getRawResponse(), TRUE);
    $num_found = $tmp['response']['numFound'];
  }
  catch (Exception $e) {
  }
  return $num_found;
}
