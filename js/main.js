(function($) {
  Drupal.behaviors.islandoraReclineJS = {
    attach: function(context, settings) {    
      var $file = Drupal.settings.islandoraReclineJS.resourceUri;
      
      // Load some data
      var dataset = new recline.Model.Dataset({
        url: $file,
        backend: 'csv'
      });

      // Now do the query to the backend to load data
      dataset.fetch();
     
      // get an element from your HTML for the viewer
      var $el = $('#islandora-recline');

      var grid = new recline.View.Grid({
        model: dataset,
        el: $el
      });
      grid.visible = true;
      grid.render();
    }
  };
})(jQuery);
