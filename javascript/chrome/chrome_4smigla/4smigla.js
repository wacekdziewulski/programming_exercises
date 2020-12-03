var LOGO_SIZE = 64;
var EXPANDED_HEIGHT = "100px";

var SITES = {
   BANGGOOD    : {url: "banggood.com", name: "banggood", logo: "img/banggood_logo_64.png", affiliate: "p=NM16185262492015094D" },
   GEARBEST    : {url: "gearbest.com", name: "gearbest", logo: "img/gearbest_logo_64.png", affiliate: "lkid=11805939" },
   HORUSRC     : {url: "horusrc.com" , name: "horusrc",  logo: "img/horusrc_logo_64.png" , affiliate: "acc=5206" },
   TOMTOP      : {url: "tomtop.com" , name: "tomtop",  logo: "img/tomtop_logo_64.png" , affiliate: "aid=4smiglapl" },
   HOBBYKING   : {url: "hobbyking.com" , name: "hobbyking",  logo: "img/hobbyking_logo_64.png" , affiliate: "affiliate_code=OKGPJSDQIOVQUSK&_asc=7916886085" },
   SURVEILZONE : {url: "surveilzone.com" , name: "surveilzone",  logo: "img/surveilzone_logo_64.png" , affiliate: "u=1058154" },
   BETAFPV     : {url: "betafpv.com" , name: "betafpv",  logo: "img/betafpv_logo_64.png" , affiliate: "sca_ref=61382.1iPDBtK4Mq" },
};

var AffiliateUrl = "";
var isExpanded = false;
var OriginalHeight;

function checkUrl(callback) {
  // Query filter to be passed to chrome.tabs.query - see
  // https://developer.chrome.com/extensions/tabs#method-query
  var queryInfo = {
    active: true,
    currentWindow: true
  };

  chrome.tabs.query(queryInfo, function(tabs) {
    var tab = tabs[0];

    var url = tab.url;
    var title = tab.title;

    console.assert(typeof url == 'string', 'tab.url should be a string');
    console.assert(typeof title == 'string', 'tab.title should be a string');

    Object.keys(SITES).forEach(function(row) {
        if (url.indexOf(SITES[row].url) != -1) {
            callback(url, SITES[row].name);
        }
    });
  });
}

function renderLogo(site) {
    var display = "none";

    Object.keys(SITES).forEach(function(row) {
        if (site === SITES[row].name) {
            var logo = document.getElementById('logo');
            logo.src = SITES[row].logo;
            logo.width = LOGO_SIZE;
            logo.height = LOGO_SIZE;
            display = "initial";
        }
    });

    document.getElementById('logo').style.display = display;
}

function clearLongUrl(url) {
    document.getElementById('link').innerHTML = "";
    document.getElementById('link').style.display = "none";
}

function renderLongUrl(url) {
    document.getElementById('link').innerHTML = url;
    document.getElementById('link').style.display = "initial";
}

function reduceView(url) {
    clearLongUrl();
    document.getElementById('main').style.height = OriginalHeight;
}

function expandView(url) {
    renderLongUrl(AffiliateUrl);
    OriginalHeight = document.getElementById('main').style.height;
    document.getElementById('main').style.height = EXPANDED_HEIGHT;
}
function displayShortUrl(url) {
    document.getElementById('short_link').innerHTML = url;
    document.getElementById('short_link').style.display = "initial";
}

function createAffiliateLink(url, site) {
    separator = '?';
    if (url.indexOf('?') != -1) {
        separator = '&';
    }

    Object.keys(SITES).forEach(function(row) {
        if (site == SITES[row].name) {
            url += separator + SITES[row].affiliate;
        }
    });

    return url;
}

function renderGooglShortLink(url) {
    var BITLY_ACCESS_TOKEN = "<hidden>";
    var BITLY_HOST = "api-ssl.bitly.com"
    var BITLY_API_URL = "https://" + BITLY_HOST + "/v4/shorten";
    var BITLY_GROUP_GUID = "Bi658MEGwBy";
    var bitlyParams = { 
        "long_url" : url,
        "group_guid" : BITLY_GROUP_GUID 
    };
    var query_json = JSON.stringify(bitlyParams);

    console.log(query_json);

    var xmlRequest = new XMLHttpRequest();
    xmlRequest.open('POST', BITLY_API_URL);
    xmlRequest.setRequestHeader("Host", BITLY_HOST);
    xmlRequest.setRequestHeader("Content-type", "application/json");
    xmlRequest.setRequestHeader("Authorization", "Bearer " + BITLY_ACCESS_TOKEN);

    xmlRequest.onload = function() {
        var response = JSON.parse(xmlRequest.responseText);
        displayShortUrl(response.link);
    };

    xmlRequest.send(query_json);
}

function copyLinkToClipboard() {
    var shortLink = document.getElementById('short_link').innerHTML;
    const input = document.createElement('input');
    input.style.position = 'fixed';
    input.style.opacity = 0;
    input.value = shortLink;
    document.body.appendChild(input);
    input.select();
    console.log(input.value);
    document.execCommand('Copy');
    document.body.removeChild(input);
    alert("Copied goo.gl link to clipboard");
}

function showMoreData() {
    if (!isExpanded) {
        isExpanded = true;
        expandView();
    }
    else {
        isExpanded = false;
        reduceView();
    }
}

document.addEventListener('DOMContentLoaded', function() {
  checkUrl(function(url, site) {
    AffiliateUrl = createAffiliateLink(url, site);
    renderLogo(site);
    renderGooglShortLink(AffiliateUrl);
  });
  document.getElementById('arrow').addEventListener('click', showMoreData);
});

