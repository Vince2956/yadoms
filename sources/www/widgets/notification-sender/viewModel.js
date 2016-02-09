widgetViewModelCtor =

/**
 * Create a notification-sender ViewModel
 * @constructor
 */
function NotificationSenderViewModel() {
   var self = this;

   // Widget identifier
   self.widget = null;

   // Observable data
   self.toCaption = ko.observable($.t("widgets/notification-sender:to"));
   self.body = ko.observable();
   self.toSelected = ko.observable();
   
   // A recipient associated to a select entry
   var recipientTuple = function(data) {
      var self = this;
      self.id = ko.observable(data.id);
      self.name = ko.observable(data.name);
   };

   // Populate "to" select
   self.toList = ko.observableArray();
   
   // Disable the optionCaption "to" of the "to" select
   self.optionsAfterRender = function(option, item) {
      option.disabled = isNullOrUndefined(item);
   }

   self.send = function() {
      // Check that widget is configured, and to/body data are valid
      if ((!isNullOrUndefined(self.widget.configuration.device)) && (self.toSelected()) && (self.body())) {
         
         var notification = new Object();
         notification.to = self.toSelected();
         notification.body = self.body();
         notification.acknowledgment = 'true';
      
         KeywordManager.sendCommand(this.widget.configuration.device.keywordId, JSON.stringify(notification));
      }
   };

   /**
    * Initialization method
    * @param widget widget class object
    */
   this.initialize = function(widget) {
      this.widget = widget;
   };
   
   /**
   * Function called when configuration change
   * @param widget widget class object
   */
   this.configurationChanged = function() {
      try {
         RecipientManager.getAll()
         .done(function(recipients) {
            $.each(recipients, function (recipientKey, recipient) {
               self.toList.push(new recipientTuple({id: recipient.id, name: recipient}));
            });
         });
      }
      catch(err) {}
   };

};
