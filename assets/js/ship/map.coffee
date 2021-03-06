define(
	['jquery', 'backbone', 'json', 'jquery.tpl', 'handlebars', 'shipctl'],
	($, Backbone, json, tpl, Handlebars, Ship) ->
		ShipMapView = Backbone.View.extend({

			initialize: ->
				this.model.on('change', this.render, this);
				# TODO poll the map
			
			render: () ->
				ship = this.model
				$("#section_map").loadTemplate('assets/html/ship/map.html', null, { afterInsert: ->
					$("#lrs_toggle_button").bind 'click', ->
						json.request('ship.toggleLongRangeScanner', [ship.get('id')], (result) ->
							ship.update(result.result)
						)

					if ship.get('lrs_active') == 0
						$('#lrs_toggle_button').text('aktivieren')
					else 
						$('#lrs_toggle_button').text('deaktivieren')

						json.request('ship.getMap', [ship.id], (result) ->
							$.get('assets/html/map/field.html', (tpl) ->
								template = Handlebars.compile(tpl);
								firstrow = true
								fields = ''
								for cy, row_x of result.result
									if (firstrow == true)
										fields += '<div><div class="map_table_y"></div>'
										for cx, map_field of row_x
											fields += '<div class="map_table_x">'+cx+'</div>'
										fields += '</div>'
										firstrow = false

									fields += '<div style="height: 34px"><div class="map_table_y">'+cy+'</div>'
									for cx, map_field of row_x
										if !map_field
											map_field = { id: 0, type_id: 0, cx: cx, cy: cy}
										if map_field.cx == ship.get('cx') and map_field.cy == ship.get('cy')
											map_field.class = 'srs_mapfield_active'
										if map_field.item_count == 0
											map_field.item_count = ''

										fields += template(map_field)
									fields += '</div>'

								$('#mapfields').html(fields)
								$('#mapfields').find('.srs_mapfield').each (index, element) ->
									element = $(element)
									if element.data('cx') == ship.get('cx') || element.data('cy') == ship.get('cy')
										element.addClass('link')
										$(element).bind 'click', ->
											Ship.move(ship, $(element).data('id'))
							, 'html')
						)
				})



		})

		return ShipMapView
);
