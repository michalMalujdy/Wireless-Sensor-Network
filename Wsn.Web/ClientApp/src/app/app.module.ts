import { ApiClientService } from './core/api-client.service';
import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { FormsModule } from '@angular/forms';
import { HttpClientModule } from '@angular/common/http';
import { RouterModule } from '@angular/router';

import { AppComponent } from './app.component';
import { NavMenuComponent } from './nav-menu/nav-menu.component';
import { HomeComponent } from './home/home.component';
import { FetchDataComponent } from './fetch-data/fetch-data.component';
import { LightReadingsComponent } from './features/readings/light-readings/light-readings.component';
import { LoggerComponent } from './features/readings/logger/logger.component';
import { ChartsComponent } from './features/charts/charts/charts.component';

@NgModule({
  declarations: [
    AppComponent,
    NavMenuComponent,
    HomeComponent,
    FetchDataComponent,
    LightReadingsComponent,
    LoggerComponent,
    ChartsComponent
  ],
  imports: [
    BrowserModule.withServerTransition({ appId: 'ng-cli-universal' }),
    HttpClientModule,
    FormsModule,
    RouterModule.forRoot([
      { path: '', component: HomeComponent, pathMatch: 'full' },
      { path: 'fetch-data', component: FetchDataComponent },
      { path: 'logs', component: LightReadingsComponent },
      { path: 'charts', component: ChartsComponent },
    ])
  ],
  providers: [ApiClientService],
  bootstrap: [AppComponent]
})
export class AppModule { }
