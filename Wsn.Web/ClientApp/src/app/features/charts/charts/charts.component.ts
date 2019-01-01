import { ApiClientService } from './../../../core/api-client.service';
import { Component, OnInit } from '@angular/core';
import { Reading } from '../../../interfaces/resources/reading';
import { DataType } from '../../../enums/DataType';
import { Chart } from 'chart.js';

@Component({
  selector: 'app-charts',
  templateUrl: './charts.component.html',
  styleUrls: ['./charts.component.css']
})
export class ChartsComponent implements OnInit {

  ngOnInit() {

  }
}
